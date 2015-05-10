#include "stdafx.h"
#include "SuperBlock.h"


SuperBlock::SuperBlock()
{
	dwBytesPerBlock = 4096;
}


SuperBlock::~SuperBlock()
{
}


VOID SuperBlock::SetSuperBlock(LPSUPERBLOCK lpBlock)
{
	size_t n = sizeof(SUPERBLOCK);
	memcpy_s(&m_SuperBlock, n, lpBlock, n);
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
	dwHeapSize = totalBlockSize;

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
	dwHeapStartAddress = dwSuperBlockBitmapStartAddress + dwSuperBlockBitmapAreaSize;

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
	m_SuperBlock.dwHeapStartAddress = dwHeapStartAddress;
	m_SuperBlock.dwHeapSize = dwHeapSize;

}

const SuperBlock::LPSUPERBLOCK SuperBlock::GetSuperBlock()
{
	size_t n = sizeof(SuperBlock::SUPERBLOCK);
	SuperBlock::LPSUPERBLOCK lpBlock = (SuperBlock::LPSUPERBLOCK)malloc(n);
	memset(lpBlock, 0, n);
	memcpy_s(lpBlock, n, &m_SuperBlock, n);
	return lpBlock;
}

DWORD SuperBlock::GetINodeStartAddress()
{
	return m_SuperBlock.dwINodeStartAddress;
}

DWORD SuperBlock::GetINodeAreaSize()
{
	return m_SuperBlock.dwINodeAreaSize;
}

DWORD SuperBlock::GetINodeBitmapStartAddress()
{
	return m_SuperBlock.dwINodeBitmapStartAddress;
}

DWORD SuperBlock::GetINodeBitmapAreaSize()
{
	return m_SuperBlock.dwINodeBitmapAreaSize;
}

DWORD SuperBlock::GetHeapStartAddress()
{
	return m_SuperBlock.dwHeapStartAddress;
}

DWORD SuperBlock::GetHeapSize()
{
	return m_SuperBlock.dwHeapSize;
}


VOID SuperBlock::SetFileName(_In_ LPCTSTR name)
{
	m_fileName = name;
}

VOID SuperBlock::Load()
{
	size_t n = sizeof(SuperBlock::SUPERBLOCK);
	fileController.Open(m_fileName);
	DWORD nSize = fileController.Read(&m_SuperBlock, n, 0);
	fileController.Close();
}

VOID SuperBlock::Save()
{
	size_t n = sizeof(SuperBlock::SUPERBLOCK);
	fileController.Open(m_fileName);
	fileController.Write(&m_SuperBlock, n, 0);
	fileController.Close();
}