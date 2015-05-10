#pragma once
#include "FileController.h"

#define EIGHTKILO 8192

class DECL_API SuperBlock
{
public:
	SuperBlock();
	~SuperBlock();

	void Init(_In_ DWORD dwSize);

	typedef struct SuperBlock_s {
		DWORD totalBlockSize;
		DWORD dwSizeSystemDB;
		DWORD dwSuperBlockAreaSize;
		DWORD dwSuperBlockBitmapAreaSize;
		DWORD dwINodeAreaSize;
		DWORD dwBytesPerBlock;
		DWORD dwSuperBlockStartAddress;
		DWORD dwINodeStartAddress;
		DWORD dwSuperBlockBitmapStartAddress;
		DWORD dwINodeBitmapAreaSize;
		DWORD dwINodeBitmapStartAddress;
		DWORD dwHeapStartAddress;
		DWORD dwHeapSize;
	} SUPERBLOCK, *LPSUPERBLOCK;

	const LPSUPERBLOCK GetSuperBlock();
	VOID SetSuperBlock(LPSUPERBLOCK lpBlock);

	DWORD GetINodeStartAddress();
	DWORD GetINodeAreaSize();
	DWORD GetINodeBitmapStartAddress();
	DWORD GetINodeBitmapAreaSize();
	DWORD GetHeapStartAddress();
	DWORD GetHeapSize();

	VOID SetFileName(_In_ LPCTSTR name);
	VOID Load();
	VOID Save();

private:
	DWORD totalBlockSize;
	DWORD dwSizeSystemDB;
	CHAR *bitmap;

	DWORD dwSuperBlockAreaSize;
	DWORD dwSuperBlockBitmapAreaSize;

	DWORD dwINodeAreaSize;
	DWORD dwINodeBitmapAreaSize;

	DWORD dwBytesPerBlock;

	SUPERBLOCK m_SuperBlock;

	DWORD dwSuperBlockStartAddress;
	DWORD dwSuperBlockBitmapStartAddress;

	DWORD dwINodeStartAddress;
	DWORD dwINodeBitmapStartAddress;

	DWORD dwHeapStartAddress;
	DWORD dwHeapSize;

	HANDLE hMutex;
	LPCTSTR m_fileName;

	FileController fileController;
};

