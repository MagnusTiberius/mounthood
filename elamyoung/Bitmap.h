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

	DWORD GetStartAddressBlock(size_t nBlocks);
	VOID SetStartAddress(DWORD dwStartAddress);
	DWORD GetStartAddress();
	VOID Load();
	DWORD GetBitmapSize();
	VOID SetBitmapSize(DWORD dwSize);

private:
	BYTE *m_lpbitmap;
	DWORD m_nBitmapSize;
	FileController fileController;
	DWORD m_dwStartAddress;

	VOID LoadBitmapM(LPVOID lpbitmap, DWORD size, DWORD dwStartAddress);

};

