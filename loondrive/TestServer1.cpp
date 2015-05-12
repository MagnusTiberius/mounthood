#include "TestServer1.h"


TestServer1::TestServer1()
{
}


TestServer1::~TestServer1()
{
}

VOID TestServer1::Start()
{
	DWORD dwThreadId = GetCurrentThreadId();
	int i;


	int nThreads = (int)SysInfo.dwNumberOfProcessors * 2;
	nThreads = 1;

	HANDLE ThreadHandle[1];

	for (i = 0; i < nThreads; i++)
	{
		ThreadHandle[i] = CreateThread(NULL, 0, ServerWorkerThread, this, 0, &ThreadID);
		if (ThreadHandle[i] == NULL)
		{
			fprintf(stderr, "%d::CreateThread() failed with error %d\n", dwThreadId, GetLastError());
			return;
		}
		else
			fprintf(stderr, "%d::CreateThread() is OK!\n", dwThreadId);

		::WaitForMultipleObjects(nThreads, ThreadHandle, true, INFINITE);

		for (i = 0; i < nThreads; i++)
		{
			CloseHandle(ThreadHandle[i]);
		}
	}

}

DWORD WINAPI TestServer1::ServerWorkerThread(LPVOID lpObject)
{
	TestServer1 *srv = (TestServer1*)lpObject;
	auto socketSrv = srv->GetSocketServer();
	while (TRUE)
	{
		socketSrv->Init(9099);
	}

}

