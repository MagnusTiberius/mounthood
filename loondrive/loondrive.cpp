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
#include "AllocatorB.h"
#include "ArrayGrowable.h"

#define TESTDB1 _T("TestDB1")
#define LOOPCOUNT 10000


int _tmain(int argc, _TCHAR* argv[])
{

#define _arraygrowable
#ifdef _arraygrowable
	ArrayGrowable arrayGrowable;
	arrayGrowable.InitArray(sizeof(int));
	for (int i = 0; i < 100; i++)
	{
		int input = 100 + (2 * i);
		arrayGrowable.PushBack(&input);
		int *n = (int*)arrayGrowable[i];
		int m = *n;
		int o = 1;
		printf("i=%d \n", m);
	}
	arrayGrowable.FreeArray();
#endif



#ifdef _allocb
	AllocatorB allocator(sizeof(int));

	for (int k = 0; k < LOOPCOUNT; k++)
	{
		int *test = NULL;
		test = (int*)allocator.Reserve();
		*test = k + 0;
		int b = *test + 5;
	}

	int *a500 = (int*)allocator[1];
	int *a600 = (int*)allocator[8000];

	allocator[600] = (void*)769;
	a600 = (int*)allocator[600];
#endif

	//Test1 test1;
	//test1.Run1();

	//TestServer1 testServer1;
	//testServer1.Start();

	//::brookwood::FileSystem fs;

	//brookwood::FileSystem::LPSUPERBLOCK lpBlock = fs.Allocate(1024 * 1024);
	//fs.Initialize(TESTDB1, 2000000);
	//fs.StartSystem(L"TestDB1");

#ifdef _dbServer
	DbServer dbServer;
	dbServer.Start();
#endif

	exit(0);

	return 0;
}

