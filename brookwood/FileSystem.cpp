#include "stdafx.h"
#include "FileSystem.h"

namespace brookwood {

	FileSystem::FileSystem()
	{
		GetSystemInfo(&SysInfo);
		dwSysGran = SysInfo.dwAllocationGranularity;
		isQuitting = false;
	}


	FileSystem::~FileSystem()
	{
	}


	VOID FileSystem::SetFileName(_In_ TCHAR *name)
	{
		m_fileName = name;
	}

	VOID FileSystem::Initialize(_In_ TCHAR *name, _In_ DWORD dwSzie)
	{
		SetFileName(name);
		Allocate(dwSzie);
		fc.Create(name, superBlock.dwEndAddress);
		fc.Open(name);
		fc.Write(&superBlock, sizeof(SUPERBLOCK), 0);
	}

	VOID FileSystem::GrowBy(_In_ DWORD dwSize)
	{
		dwGrowBySize = dwSize;
	}

	/*
	-----------------------------

	Superbock
	-----------------------------


	Inode
	-----------------------------

	Inode Bitmap
	-----------------------------

	Heap Bitmap
	-----------------------------


	Heap
	-----------------------------
	Meta
	-----------------------------

	*/
	const FileSystem::LPSUPERBLOCK FileSystem::Allocate(_In_ DWORD dwSzie)
	{
		memset(&superBlock, 0, sizeof(SUPERBLOCK));
		superBlock.dwBytesPerBlock = 4096;
		superBlock.dwHeapBlockSize = (dwSzie / superBlock.dwBytesPerBlock) + 1;
		superBlock.dwHeapSize = superBlock.dwHeapBlockSize * superBlock.dwBytesPerBlock;
		superBlock.dwSuperBlockStartAddress = 0;

		size_t nSuperBlockSize = sizeof(SUPERBLOCK);
		superBlock.dwINodeStartAddress = ((nSuperBlockSize / 64) + 1) * 64;

		size_t nInodeBlockSize = superBlock.dwHeapBlockSize * sizeof(INODE);
		superBlock.dwINodeAreaSize = nInodeBlockSize * sizeof(INODE);
		superBlock.dwINodeBitmapStartAddress = superBlock.dwINodeStartAddress + superBlock.dwINodeAreaSize;
		superBlock.dwINodeBitmapAreaSize = nInodeBlockSize;

		superBlock.dwHeapBitmapStartAddress = superBlock.dwINodeBitmapAreaSize + superBlock.dwINodeBitmapAreaSize;
		superBlock.dwHeapBitmapAreaSize = nInodeBlockSize;

		superBlock.dwHeapStartAddress = superBlock.dwHeapBitmapStartAddress + superBlock.dwHeapBitmapAreaSize;
		superBlock.dwHeapSize = superBlock.dwHeapBlockSize * superBlock.dwBytesPerBlock;

		superBlock.dwMetaStartAddress = superBlock.dwHeapStartAddress + superBlock.dwHeapSize;
		superBlock.dwMetaAreaSize = 256;

		superBlock.dwEndAddress = superBlock.dwMetaStartAddress + superBlock.dwMetaAreaSize;

		return &superBlock;
	}

	VOID FileSystem::ReadInode(_Out_ LPINODE lpNode, _In_ DWORD dwIndex)
	{
		DWORD displacement = dwIndex * sizeof(INODE);
		DWORD effectiveAddress = superBlock.dwINodeStartAddress + displacement;
		fc.Open(m_fileName);
		fc.Read(lpNode, sizeof(INODE), effectiveAddress);
		fc.Close();
	}

	VOID FileSystem::WriteInode(_In_ LPINODE lpNode, _In_ DWORD dwIndex)
	{
		DWORD displacement = dwIndex * sizeof(INODE);
		DWORD effectiveAddress = superBlock.dwINodeStartAddress + displacement;
		fc.Open(m_fileName);
		fc.Write(lpNode, sizeof(INODE), effectiveAddress);
		fc.Close();
	}

	VOID FileSystem::ReadBitmap(_Out_ LPBITMAP lpBitmap, _In_ DWORD dwSize, _In_ DWORD dwStartAddress)
	{
		fc.Open(m_fileName);
		fc.Read(lpBitmap, dwSize, dwStartAddress);
		fc.Close();
	}

	VOID FileSystem::WriteBitmapBits(_In_ std::vector<BYTE> *list, _In_ DWORD dwStartAddress)
	{
		std::vector<BYTE>::iterator it;
		BYTE buffer[1];
		DWORD dwSize = 1;
		fc.Open(m_fileName);
		for (it = list->begin(); it != list->end(); it++)
		{
			auto value = *it;
			memcpy_s(&buffer[1], 1, &value, 1);
		}
		fc.Write(buffer, dwSize, dwStartAddress);
		fc.Close();
	}

	VOID FileSystem::StartSystem(TCHAR *name)
	{
		m_fileName = name;
		StartSystem();
	}

	VOID FileSystem::StartSystem(void)
	{
		DWORD dwThreadId = GetCurrentThreadId();
		int i;

		fc.Open(m_fileName);
		fc.Read(&superBlock, sizeof(SUPERBLOCK), 0);

		GetSystemInfo(&SysInfo);

		int nThreads = (int)SysInfo.dwNumberOfProcessors * 2;
		nThreads = NTHREADS;

		HANDLE hThreads[NTHREADS];

		for (i = 0; i < nThreads; i++)
		{
			hThreads[i] = CreateThread(NULL, 0, ServerWorkerThread, this, 0, &ThreadID);
			if (hThreads[i] == NULL)
			{
				fprintf(stderr, "%d::CreateThread() failed with error %d\n", dwThreadId, GetLastError());
				return;
			}
			else
				fprintf(stderr, "%d::CreateThread() is OK!\n", dwThreadId);

		}
		//::WaitForMultipleObjects(2, hThreads, true, INFINITE);
		//for (i = 0; i < nThreads; i++)
		//{
		//	CloseHandle(hThreads[i]);
		//}
	}

	DWORD WINAPI FileSystem::ServerWorkerThread(LPVOID lpObject)
	{
		FileSystem *fs = (FileSystem*)lpObject;
		while (!fs->IsQuitting())
		{
			//printf(".");
		}
		return 0;
	}

}