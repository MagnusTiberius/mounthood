#pragma once
#include "stdafx.h"
#include "FileController.h"
#include "FileSemantic.h"
#include <vector>

#define NTHREADS 3

namespace brookwood {

	class FileSystem
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


		typedef struct TaskRequest_s {
			CHAR *request;
			size_t requestLength;
			CHAR *reply;
			size_t replyLength;
			SOCKET Socket;
			LPVOID lpSocketInfo;
		} TASKREQUEST, *LPTASKREQUEST;

		typedef std::deque<TASKREQUEST> STACKTASKREQUEST;

	public:
		VOID SetFileName(_In_ TCHAR *name);
		VOID Initialize(_In_ TCHAR *name, _In_ DWORD dwSzie);
		const LPSUPERBLOCK Allocate(_In_ DWORD dwSzie);
		VOID GrowBy(_In_ DWORD dwSize);
		VOID ReadInode(_In_ LPINODE lpNode, _In_ DWORD dwIndex);
		VOID WriteInode(_In_ LPINODE lpNode, _In_ DWORD dwIndex);

		VOID ReadBitmap(_Out_ LPBITMAP lpBitmap, _In_ DWORD dwSize, _In_ DWORD dwStartAddress);
		VOID WriteBitmapBits(_In_ std::vector<BYTE> *list, _In_ DWORD dwStartAddress);
		VOID StartSystem(void);
		VOID StartSystem(TCHAR *name);

		static DWORD WINAPI ServerWorkerThread(LPVOID CompletionPortID);

		bool IsQuitting()
		{
			return isQuitting;
		}

		HANDLE ghWriteEvent;
		HANDLE ghTaskQueueNotEmpty;
		HANDLE ghMutex;

		virtual VOID PopTaskRequest(_Out_ LPVOID lpTaskRequest)
		{
			printf("virtual proc\n");
		}

	private:
		SUPERBLOCK superBlock;
		FileController fc;
		FileSemantic fs;
		TCHAR *m_fileName;
		DWORD dwGrowBySize;
		SYSTEM_INFO SysInfo;
		DWORD dwSysGran;

		LPBITMAP lpInodeBitmap;
		HANDLE ThreadHandle;
		DWORD ThreadID;
		bool isQuitting;
	};

}