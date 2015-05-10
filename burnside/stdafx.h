// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define SYSDB L"SystemDB.dat"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include "FileAPI.h"

#include <cassert>
#include <assert.h> 

#ifdef BURNSIDE_EXPORTS
#define DECL_API __declspec(dllexport)
#else
#define DECL_API __declspec(dllimport)
#endif

// TODO: reference additional headers your program requires here
