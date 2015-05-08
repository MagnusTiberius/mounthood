#include "stdafx.h"
#include "SuperBlock.h"


SuperBlock::SuperBlock()
{
	dwBytesPerBlock = 4096;
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

	totalBlockSize = (dwSizeSystemDB - dwHeaderSize) / dwBytesPerBlock;

	while (dwBitmapAreaSize < totalBlockSize)
	{
		dwBitmapAreaSize = dwBitmapAreaSize + (EIGHTKILO / 2);
		dwHeaderSize = dwSuperBlockAreaSize + dwBitmapAreaSize + dwINodeAreaSize;
		assert(dwSizeSystemDB > dwHeaderSize);
		totalBlockSize = (dwSizeSystemDB - dwHeaderSize) / dwBytesPerBlock;
	}

	assert(dwBitmapAreaSize >= totalBlockSize);

	dwSuperBlockStartAddress = 0;
	dwINodeStartAddress = dwSuperBlockStartAddress + dwSuperBlockAreaSize;
	dwBitmapStartAddress = dwINodeStartAddress + dwINodeAreaSize;

	m_SuperBlock.dwSuperBlockAreaSize = dwSuperBlockAreaSize;
	m_SuperBlock.dwBitmapAreaSize = dwBitmapAreaSize;
	m_SuperBlock.dwINodeAreaSize = dwINodeAreaSize;
	m_SuperBlock.dwSizeSystemDB = dwSizeSystemDB;
	m_SuperBlock.dwBytesPerBlock = dwBytesPerBlock;
	m_SuperBlock.totalBlockSize = totalBlockSize;

	m_SuperBlock.dwSuperBlockStartAddress = dwSuperBlockStartAddress;
	m_SuperBlock.dwINodeStartAddress = dwINodeStartAddress;
	m_SuperBlock.dwBitmapStartAddress = dwBitmapStartAddress;

}