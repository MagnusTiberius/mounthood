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

	SuperBlock superBlock;
	FileController fileController;
	SuperBlock::SUPERBLOCK aBlock;
	size_t n = sizeof(SuperBlock::SUPERBLOCK);
	memset(&aBlock, 0, n);
	fileController.Open(SYSDB);
	DWORD m = fileController.Read(&aBlock,n,0);
	fileController.Close();

	Bitmap bitmap;
	bitmap.SetBitmapSize(aBlock.dwINodeBitmapAreaSize);
	bitmap.SetStartAddress(aBlock.dwINodeBitmapStartAddress);
	bitmap.Load();
	exit(0);
	return 0;
}

