#include "stdafx.h"
#include "FileSystem.h"

namespace burnside {

	FileSystem::FileSystem()
	{
		GetSystemInfo(&SysInfo);
		dwSysGran = SysInfo.dwAllocationGranularity;
	}


	FileSystem::~FileSystem()
	{
	}


	VOID FileSystem::SetFileName(_In_ LPCTSTR name)
	{
		m_fileName = name;
	}

	VOID FileSystem::Initialize(_In_ LPCTSTR name, _In_ DWORD dwSzie)
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


	VOID FileSystem::ReadInode(_In_ LPINODE lpNode, _In_ DWORD dwIndex)
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

}