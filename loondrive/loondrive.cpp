// loondrive.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SystemDB.h"
#include "SuperBlock.h"
#include "FileController.h"
#include "Bitmap.h"
#include "Inode.h"
#include "FileSystem.h"
#include "Test1.h"

#define TESTDB1 L"TestDB1"

int _tmain(int argc, _TCHAR* argv[])
{
	//Test1 test1;
	//test1.Run1();


	::burnside::FileSystem fs;

	burnside::FileSystem::LPSUPERBLOCK lpBlock = fs.Allocate(1024 * 1024);
	fs.Initialize(TESTDB1, 2000000);

	exit(0);

	return 0;
}

