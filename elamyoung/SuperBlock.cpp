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
	dwSuperBlockBitmapAreaSize = EIGHTKILO;
	dwINodeBitmapAreaSize = EIGHTKILO;
	dwINodeAreaSize = (EIGHTKILO * 3);
	dwSizeSystemDB = dwSize;
	DWORD dwHeaderSize = dwSuperBlockAreaSize + dwSuperBlockBitmapAreaSize + dwINodeAreaSize + dwINodeBitmapAreaSize;
	assert(dwSizeSystemDB > dwHeaderSize);

	totalBlockSize = (dwSizeSystemDB - dwHeaderSize) / dwBytesPerBlock;


	while (dwSuperBlockBitmapAreaSize < totalBlockSize)
	{
		dwSuperBlockBitmapAreaSize = dwSuperBlockBitmapAreaSize + (EIGHTKILO / 2);
		dwINodeBitmapAreaSize = dwSuperBlockBitmapAreaSize;
		dwHeaderSize = dwSuperBlockAreaSize + dwSuperBlockBitmapAreaSize + dwINodeAreaSize;
		assert(dwSizeSystemDB > dwHeaderSize);
		totalBlockSize = (dwSizeSystemDB - dwHeaderSize) / dwBytesPerBlock;
	}

	assert(dwSuperBlockBitmapAreaSize >= totalBlockSize);

	dwSuperBlockStartAddress = 0;
	dwINodeStartAddress = dwSuperBlockStartAddress + dwSuperBlockAreaSize;
	dwINodeBitmapStartAddress = dwINodeStartAddress + dwINodeAreaSize;
	dwSuperBlockBitmapStartAddress = dwINodeBitmapStartAddress + dwINodeBitmapAreaSize;

	m_SuperBlock.dwSuperBlockAreaSize = dwSuperBlockAreaSize;
	m_SuperBlock.dwSuperBlockBitmapAreaSize = dwSuperBlockBitmapAreaSize;
	m_SuperBlock.dwINodeAreaSize = dwINodeAreaSize;
	m_SuperBlock.dwSizeSystemDB = dwSizeSystemDB;
	m_SuperBlock.dwBytesPerBlock = dwBytesPerBlock;
	m_SuperBlock.totalBlockSize = totalBlockSize;
	m_SuperBlock.dwSuperBlockStartAddress = dwSuperBlockStartAddress;
	m_SuperBlock.dwINodeStartAddress = dwINodeStartAddress;
	m_SuperBlock.dwSuperBlockBitmapStartAddress = dwSuperBlockBitmapStartAddress;
	m_SuperBlock.dwINodeBitmapAreaSize = dwINodeBitmapAreaSize;
	m_SuperBlock.dwINodeBitmapStartAddress = dwINodeBitmapStartAddress;

}

const SuperBlock::LPSUPERBLOCK SuperBlock::GetSuperBlock()
{
	size_t n = sizeof(SuperBlock::SUPERBLOCK);
	SuperBlock::LPSUPERBLOCK lpBlock = (SuperBlock::LPSUPERBLOCK)malloc(n);
	memset(lpBlock, 0, n);
	memcpy_s(lpBlock, n, &m_SuperBlock, n);
	return lpBlock;
}