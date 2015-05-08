#include "Bitmap.h"


Bitmap::Bitmap()
{
}


Bitmap::~Bitmap()
{
}


DWORD Bitmap::GetStartAddressBlock(size_t nBlocks)
{
	DWORD dwAddress = -1;

	return dwAddress;
}

VOID Bitmap::LoadBitmapM(LPVOID lpbitmap, DWORD size, DWORD dwStartAddress)
{
	fileController.Open(SYSDB);
	m_nBitmapSize = fileController.Read(lpbitmap, size, dwStartAddress);
	m_lpbitmap = (BYTE*)lpbitmap;
	fileController.Close();
}

VOID Bitmap::SetStartAddress(DWORD dwStartAddress)
{
	m_dwStartAddress = dwStartAddress;
}

DWORD Bitmap::GetStartAddress()
{
	return m_dwStartAddress;
}

VOID Bitmap::SetBitmapSize(DWORD dwSize)
{
	m_nBitmapSize = dwSize;
	if (m_lpbitmap != NULL)
	{
		free(m_lpbitmap);
	}
	m_lpbitmap = (BYTE*)malloc(m_nBitmapSize);
	memset(m_lpbitmap, 0, m_nBitmapSize);
}

DWORD Bitmap::GetBitmapSize()
{
	return m_nBitmapSize;
}


VOID Bitmap::Load()
{
	LoadBitmapM((LPVOID)m_lpbitmap, m_nBitmapSize, m_dwStartAddress);
}