#include "Bitmap.h"


Bitmap::Bitmap()
{
	m_lpbitmap = NULL;
}


Bitmap::~Bitmap()
{
}


DWORD Bitmap::GetStartAddressBlock(_In_ size_t nBlocks)
{
	DWORD dwAddress = -1;

	return dwAddress;
}

VOID Bitmap::LoadBitmapM(_Inout_ LPVOID lpbitmap, _In_ DWORD size, _In_ DWORD dwStartAddress)
{
	fileController.Open(m_fileName);
	m_nBitmapSize = fileController.Read(lpbitmap, size, dwStartAddress);
	m_lpbitmap = (BYTE*)lpbitmap;
	fileController.Close();
	BYTE test = -1;
	test = m_lpbitmap[m_nBitmapSize-1];
	assert(test != -1);
}

VOID Bitmap::SaveBitmapM(_Inout_ LPVOID lpbitmap, _In_ DWORD size, _In_ DWORD dwStartAddress)
{
	fileController.Open(m_fileName);
	fileController.Write(lpbitmap, size, dwStartAddress);
	fileController.Close();
}


VOID Bitmap::SetStartAddress(_In_ DWORD dwStartAddress)
{
	m_dwStartAddress = dwStartAddress;
}

DWORD Bitmap::GetStartAddress()
{
	return m_dwStartAddress;
}

VOID Bitmap::SetBitmapSize(_In_ DWORD dwSize)
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

VOID Bitmap::Save()
{
	SaveBitmapM((LPVOID)m_lpbitmap, m_nBitmapSize, m_dwStartAddress);
}

VOID Bitmap::SetFileName(_In_ LPCTSTR name)
{
	m_fileName = name;
}

DWORD Bitmap::FindAddressBlockToReserve(_In_ DWORD dwCount)
{
	DWORD dwMatchCtr = 0;
	DWORD dwAddress = 0;
	for (DWORD i = 0; i < m_nBitmapSize; i++)
	{
		BYTE c = m_lpbitmap[i];
		if (c == 0)
		{
			if (dwMatchCtr == 0)
			{
				dwAddress = i;
			}
			dwMatchCtr = dwMatchCtr + 1;
			if (dwMatchCtr == dwCount)
			{
				return dwAddress;
			}
		}
		else
		{
			dwMatchCtr = 0;
			dwAddress = 0;
		}
	}
	return -1;
}

DWORD Bitmap::ReserveBlock(_In_ DWORD dwIndex, _In_ DWORD dwCount)
{
	for (DWORD i = dwIndex; i < dwIndex + dwCount; i++)
	{
		m_lpbitmap[i] = 1;
	}
	return 0;
}