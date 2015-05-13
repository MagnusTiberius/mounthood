// hawthorne.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SystemDB.h"
#include "SuperBlock.h"
#include "FileController.h"
#include "Bitmap.h"
#include "Inode.h"
#include "FileSystem.h"
#include "SocketSelectServer.h"
#include "SocketClient.h"

#define TESTDB1 L"TestDB1"

int _tmain(int argc, _TCHAR* argv[])
{
	brookwood::SocketClient socketClient;
	socketClient.SetPort(9099);
	socketClient.Connect();
	socketClient.Send("1 CREATE TABLE pet (name VARCHAR(20), owner VARCHAR(20),species VARCHAR(20), sex CHAR(1), birth DATE, death DATE); ");
	socketClient.Send("2 CREATE TABLE pet (name VARCHAR(20), owner VARCHAR(20),species VARCHAR(20), sex CHAR(1), birth DATE, death DATE); ");
	socketClient.Send("3 CREATE TABLE pet (name VARCHAR(20), owner VARCHAR(20),species VARCHAR(20), sex CHAR(1), birth DATE, death DATE); ");
	socketClient.Send("4 CREATE TABLE pet (name VARCHAR(20), owner VARCHAR(20),species VARCHAR(20), sex CHAR(1), birth DATE, death DATE); ");

	return 0;
}

