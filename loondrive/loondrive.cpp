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
#include "SocketSelectServer.h"
#include "TestServer1.h"
#include "DbServer.h"

#define TESTDB1 _T("TestDB1")

int _tmain(int argc, _TCHAR* argv[])
{
	//Test1 test1;
	//test1.Run1();

	//TestServer1 testServer1;
	//testServer1.Start();

	//::brookwood::FileSystem fs;

	//brookwood::FileSystem::LPSUPERBLOCK lpBlock = fs.Allocate(1024 * 1024);
	//fs.Initialize(TESTDB1, 2000000);
	//fs.StartSystem(L"TestDB1");

	DbServer dbServer;
	dbServer.Start();

	exit(0);

	return 0;
}

