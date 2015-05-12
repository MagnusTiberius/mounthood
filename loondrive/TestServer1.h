#pragma once
#include "stdafx.h"
#include "SystemDB.h"
#include "SuperBlock.h"
#include "FileController.h"
#include "Bitmap.h"
#include "Inode.h"
#include "FileSystem.h"
#include "Test1.h"
#include "SocketSelectServer.h"


class TestServer1
{
public:
	TestServer1();
	~TestServer1();

	VOID Start();
	static DWORD WINAPI ServerWorkerThread(LPVOID lpObject);

	brookwood::SocketSelectServer* GetSocketServer()
	{
		return &socketSelectServer;
	}


private:
	brookwood::SocketSelectServer socketSelectServer;

	HANDLE ThreadHandle;
	DWORD ThreadID;
	SYSTEM_INFO SysInfo;

};

