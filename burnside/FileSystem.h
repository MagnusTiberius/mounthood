#pragma once
#include "stdafx.h"
#include "FileController.h"
#include "FileSemantic.h"

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
		} INODE, *LPINODE;


		typedef struct FileSystem_s {
			SUPERBLOCK SuperBlock;
		} FILESYSTEM, *LPFILESYSTEM;

		VOID SetFileName(_In_ LPCTSTR name);

		VOID Initialize(_In_ LPCTSTR name, _In_ DWORD dwSzie);

		const LPSUPERBLOCK Allocate(_In_ DWORD dwSzie);

		VOID GrowBy(_In_ DWORD dwSize);

	private:
		SUPERBLOCK superBlock;
		FileController fc;
		FileSemantic fs;
		LPCTSTR m_fileName;
		DWORD dwGrowBySize;
		SYSTEM_INFO SysInfo;
		DWORD dwSysGran;
	};

}