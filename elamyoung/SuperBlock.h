#pragma once
#include "FileController.h"

#define EIGHTKILO 8192

class SuperBlock
{
public:
	SuperBlock();
	~SuperBlock();

	void Init(_In_ DWORD dwSize);

	typedef struct SuperBlock_s {
		DWORD totalBlockSize;
		DWORD dwSizeSystemDB;
		DWORD dwSuperBlockAreaSize;
		DWORD dwBitmapAreaSize;
		DWORD dwINodeAreaSize;
		DWORD dwBytesPerBlock;
		DWORD dwSuperBlockStartAddress;
		DWORD dwINodeStartAddress;
		DWORD dwBitmapStartAddress;
	} SUPERBLOCK, *LPSUPERBLOCK;


private:
	DWORD totalBlockSize;
	CHAR *bitmap;
	DWORD dwSizeSystemDB;
	DWORD dwSuperBlockAreaSize;
	DWORD dwBitmapAreaSize;
	DWORD dwINodeAreaSize;
	DWORD dwBytesPerBlock;

	SUPERBLOCK m_SuperBlock;

	DWORD dwSuperBlockStartAddress;
	DWORD dwINodeStartAddress;
	DWORD dwBitmapStartAddress;

};

