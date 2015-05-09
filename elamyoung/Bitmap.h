#pragma once
#include "stdafx.h"

#include "FileController.h"

class DECL_API Bitmap
{
public:
	Bitmap();
	~Bitmap();

	typedef struct Bitmap_s {
		CHAR *bitmap;
	} BITMAP, *LPBITMAP;

	DWORD GetStartAddressBlock(_In_ size_t nBlocks);
	VOID SetStartAddress(_In_ DWORD dwStartAddress);
	DWORD GetStartAddress();
	VOID Load();
	VOID Save();
	DWORD GetBitmapSize();
	VOID SetBitmapSize(_In_ DWORD dwSize);
	VOID SetFileName(_In_ LPCTSTR name);
	DWORD FindAddressBlockToReserve(_In_ DWORD dwCount);
	DWORD ReserveBlock(_In_ DWORD dwIndex, _In_ DWORD dwCount);

private:
	BYTE *m_lpbitmap;
	DWORD m_nBitmapSize;
	FileController fileController;
	DWORD m_dwStartAddress;

	VOID LoadBitmapM(_Inout_ LPVOID lpbitmap, _In_ DWORD size, _In_ DWORD dwStartAddress);
	VOID SaveBitmapM(_Inout_ LPVOID lpbitmap, _In_ DWORD size, _In_ DWORD dwStartAddress);

	LPCTSTR m_fileName;

};

