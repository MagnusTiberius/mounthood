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
	} SUPERBLOCK, *LPSUPERBLOCK;

	const LPSUPERBLOCK GetSuperBlock();

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

	HANDLE hMutex;

};

