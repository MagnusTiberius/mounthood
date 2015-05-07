// loondrive.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileController.h"

int _tmain(int argc, _TCHAR* argv[])
{
	FileController fileController;
	fileController.Init(L"SystemDB.dat", 1024);
	return 0;
}

