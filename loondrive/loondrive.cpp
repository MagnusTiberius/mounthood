// loondrive.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SystemDB.h"

int _tmain(int argc, _TCHAR* argv[])
{
	SystemDB systemDB;
	systemDB.InitSystem();
	systemDB.InitHeader();
	return 0;
}

