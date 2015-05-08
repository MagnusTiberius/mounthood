#include "stdafx.h"
#include "SuperBlock.h"


SuperBlock::SuperBlock()
{
}


SuperBlock::~SuperBlock()
{
}


void SuperBlock::Init(_In_ DWORD dwSize)
{
	dwSuperBlockAreaSize = EIGHTKILO;
	dwBitmapAreaSize = EIGHTKILO;
	dwINodeAreaSize = (EIGHTKILO * 3);
	dwSizeSystemDB = dwSize;
	DWORD dwHeaderSize = dwSuperBlockAreaSize + dwBitmapAreaSize + dwINodeAreaSize;
	assert(dwSizeSystemDB > dwHeaderSize);
	totalBlockSize = (dwSizeSystemDB - dwHeaderSize) / 4096;
}