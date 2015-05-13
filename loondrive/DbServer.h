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
		ULONG len = pSocketInfo->DataBuf.len;
		PushTaskRequest(msg, len, pSocketInfo->Socket, pSocketInfo);
		memset(&pSocketInfo->BufferOut, 0, DATA_BUFSIZE);
		memcpy_s(&pSocketInfo->BufferOut, len, pSocketInfo->DataBuf.buf, len);
		pSocketInfo->DataBufOut.buf = pSocketInfo->BufferOut;
		pSocketInfo->DataBufOut.len = strlen(pSocketInfo->BufferOut);
		pSocketInfo->BytesSEND = strlen(pSocketInfo->BufferOut);
	}

	void Start()
	{
		StartSystem(L"TestDB1");
		StartSocketServer();
		while (TRUE)
		{

		}
	}

	VOID PushTaskRequest(CHAR *requestMsg, ULONG len, SOCKET Socket, LPSOCKET_INFORMATION pSocketInfo)
	{
		bool isEmpty = false;
		TASKREQUEST req;
		memset(&req, 0, sizeof(TASKREQUEST));
		req.request = (CHAR*)malloc(len);
		memset(req.request, 0, len );
		req.request = _strdup(requestMsg);
		req.requestLength = strlen(req.request);
		req.Socket = Socket;
		req.lpSocketInfo = (LPVOID)pSocketInfo;
		if (stackTaskRequest.size() == 0)
		{
			isEmpty = true;
		}
		stackTaskRequest.push_back(req);
		if (stackTaskRequest.size() > 0 && isEmpty == true)
		{
			SetEvent(ghTaskQueueNotEmpty);
		}
	}

	VOID PopTaskRequest(_Out_ LPVOID lpTaskRequest)
	{
		size_t len = sizeof(TASKREQUEST);
		LPTASKREQUEST lptrq = (LPTASKREQUEST)malloc(len);
		memset(lptrq, 0, len);
		if (stackTaskRequest.size() > 0)
		{
			memcpy_s(lptrq, len, &stackTaskRequest[0], len);
			memcpy_s(lpTaskRequest, len, &stackTaskRequest[0], len);
			stackTaskRequest.pop_front();
		}
		if (stackTaskRequest.size() == 0)
		{
			ResetEvent(ghTaskQueueNotEmpty);
		}
	}


private:
	STACKTASKREQUEST stackTaskRequest;

};

