// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <queue>
#include <deque>

typedef struct TaskRequest_s {
	CHAR *request;
	size_t requestLength;
	CHAR *reply;
	size_t replyLength;
	SOCKET Socket;
} TASKREQUEST, *LPTASKREQUEST;

typedef std::deque<TASKREQUEST> STACKTASKREQUEST;

// TODO: reference additional headers your program requires here
