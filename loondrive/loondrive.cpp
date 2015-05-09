// loondrive.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SystemDB.h"
#include "SuperBlock.h"
#include "FileController.h"
#include "Bitmap.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SystemDB systemDB;
	systemDB.InitSystem();

	//
	// Superblock testing.
	//
	SuperBlock superBlock;
	FileController fileController;
	SuperBlock::SUPERBLOCK aBlock;
	size_t n = sizeof(SuperBlock::SUPERBLOCK);
	memset(&aBlock, 0, n);
	fileController.Open(SYSDB);
	DWORD m = fileController.Read(&aBlock,n,0);
	fileController.Close();

	//
	// Bitmap testing.
	//
	Bitmap bitmap;
	bitmap.SetFileName(SYSDB);
	bitmap.SetBitmapSize(aBlock.dwINodeBitmapAreaSize);
	bitmap.SetStartAddress(aBlock.dwINodeBitmapStartAddress);
	bitmap.Load();
	DWORD nSizeBitmap = bitmap.GetBitmapSize();
	DWORD dwAddress1 = bitmap.FindAddressBlockToReserve(20);
	assert(dwAddress1 == 0);
	bitmap.ReserveBlock(dwAddress1, 20);
	DWORD dwAddress2 = bitmap.FindAddressBlockToReserve(23);
	assert(dwAddress2 == 20);
	bitmap.ReserveBlock(dwAddress2, 23);
	DWORD dwAddress3 = bitmap.FindAddressBlockToReserve(23);
	assert(dwAddress3 == 43);
	bitmap.ReserveBlock(dwAddress3, 23);
	bitmap.Save();

	//
	// Test if bitmap got saved, load it back and reserve more blocks.
	//
	Bitmap bitmap2;
	bitmap2.SetFileName(SYSDB);
	bitmap2.SetBitmapSize(aBlock.dwINodeBitmapAreaSize);
	bitmap2.SetStartAddress(aBlock.dwINodeBitmapStartAddress);
	bitmap2.Load();
	DWORD nSizeBitmap2 = bitmap.GetBitmapSize();
	DWORD dwAddress4 = bitmap.FindAddressBlockToReserve(73);
	bitmap.Save();

	exit(0);

	return 0;
}

