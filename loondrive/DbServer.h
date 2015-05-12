#pragma once
#include "stdafx.h"
#include "SocketSelectServer.h"
#include "FileSystem.h"

#define TESTDB1 _T("TestDB1")

using namespace brookwood;

class DbServer : public SocketSelectServer, public FileSystem
{
public:
	DbServer();
	~DbServer();

	virtual void HandleRequest(LPSOCKET_INFORMATION pSocketInfo)
	{
		CHAR *msg = pSocketInfo->DataBuf.buf;
	}

	void Start()
	{
		StartSystem(L"TestDB1");
		StartSocketServer();

		while (TRUE)
		{

		}

	}

};

