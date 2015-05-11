#pragma once
#include "stdafx.h"
#include "FileController.h"
#include "FileSemantic.h"
#include <vector>

namespace burnside {

	class DECL_API FileSystem
	{
	public:
		FileSystem();
		~FileSystem();

		typedef struct SuperBlock_s {
			DWORD totalBlockSize;
			DWORD dwSizeSystemDB;
			DWORD dwSuperBlockAreaSize;
			DWORD dwSuperBlockBitmapAreaSize;
			DWORD dwBytesPerBlock;
			DWORD dwSuperBlockBitmapStartAddress;
			DWORD dwSuperBlockStartAddress;
			DWORD dwINodeAreaSize;
			DWORD dwINodeStartAddress;
			DWORD dwINodeBitmapAreaSize;
			DWORD dwINodeBitmapStartAddress;
			DWORD dwHeapBitmapStartAddress;
			DWORD dwHeapBitmapAreaSize;
			DWORD dwHeapStartAddress;
			DWORD dwHeapSize;
			DWORD dwHeapBlockSize;
			DWORD dwMetaStartAddress;
			DWORD dwMetaAreaSize;
			DWORD dwEndAddress;
		} SUPERBLOCK, *LPSUPERBLOCK;


		enum INODETYPE {
			INODETYPE_UNDEFINED = 0,
			INODETYPE_SYSTABLE = 1,
			INODETYPE_TABLE = 2,
			INODETYPE_INDEX = 4,
			INODETYPE_TABLEDEF = 8,
			INODETYPE_INDEXDEF = 16,
		};

		// An INode is 256 bytes long.
		typedef struct INode_s {
			INODETYPE enInodeType;
			DWORD dwStartAddress;
			DWORD dwStartBitmapHeapAddress;
			DWORD dwStartBitmapHeapReserveCount;
			DWORD dwStartInodeBitmapAddress;
			DWORD bIsLocked;
			DWORD dwReaderCount;
			DWORD dwWriterWaitingFlag;
			DWORD nextInode;
		} INODE, *LPINODE;


		typedef struct FileList_s {
			DWORD dwID;
			DWORD dwInodeID;
			TCHAR szName[256];
		} FILELIST, *LPFILELIST;

		typedef struct FileSystem_s {
			SUPERBLOCK SuperBlock;
		} FILESYSTEM, *LPFILESYSTEM;

		typedef struct Bitmap_s {
			BYTE *bitmap;
		} BITMAP, *LPBITMAP;

		VOID SetFileName(_In_ LPCTSTR name);
		VOID Initialize(_In_ LPCTSTR name, _In_ DWORD dwSzie);
		const LPSUPERBLOCK Allocate(_In_ DWORD dwSzie);
		VOID GrowBy(_In_ DWORD dwSize);
		VOID ReadInode(_In_ LPINODE lpNode, _In_ DWORD dwIndex);
		VOID WriteInode(_In_ LPINODE lpNode, _In_ DWORD dwIndex);

		VOID CreateTable(_In_ LPCTSTR name)
		{
			INODE inode;
			Reserve(&inode);
		}

		VOID Reserve(LPINODE inode)
		{

		}

		VOID GetFreeInode()
		{

		}

		VOID ReadBitmap(_Out_ LPBITMAP lpBitmap, _In_ DWORD dwSize, _In_ DWORD dwStartAddress);
		VOID WriteBitmapBits(_In_ std::vector<BYTE> *list, _In_ DWORD dwStartAddress);

		static DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID);

		VOID Start();

	private:
		SUPERBLOCK superBlock;
		FileController fc;
		FileSemantic fs;
		LPCTSTR m_fileName;
		DWORD dwGrowBySize;
		SYSTEM_INFO SysInfo;
		DWORD dwSysGran;

		LPBITMAP lpInodeBitmap;
		HANDLE ThreadHandle;
		DWORD ThreadID;
	};

}