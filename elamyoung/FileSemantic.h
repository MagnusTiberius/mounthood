#pragma once

#include "stdafx.h"

class DECL_API FileSemantic
{
public:
	FileSemantic();
	~FileSemantic();

	HANDLE HCreateFile(
		_In_     LPCTSTR               lpFileName,
		_In_     DWORD                 dwDesiredAccess,
		_In_     DWORD                 dwShareMode,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes,
		_In_     DWORD                 dwCreationDisposition,
		_In_     DWORD                 dwFlagsAndAttributes,
		_In_opt_ HANDLE                hTemplateFile);

	BOOL HReadFile(
		_In_        HANDLE       hFile,
		_Out_       LPVOID       lpBuffer,
		_In_        DWORD        nNumberOfBytesToRead,
		_Out_opt_   LPDWORD      lpNumberOfBytesRead,
		_Inout_opt_ LPOVERLAPPED lpOverlapped);

	BOOL HWriteFile(
		_In_        HANDLE       hFile,
		_In_        LPCVOID      lpBuffer,
		_In_        DWORD        nNumberOfBytesToWrite,
		_Out_opt_   LPDWORD      lpNumberOfBytesWritten,
		_Inout_opt_ LPOVERLAPPED lpOverlapped);

	HANDLE HCreateFileMapping(
		_In_     HANDLE                hFile,
		_In_opt_ LPSECURITY_ATTRIBUTES lpAttributes,
		_In_     DWORD                 flProtect,
		_In_     DWORD                 dwMaximumSizeHigh,
		_In_     DWORD                 dwMaximumSizeLow,
		_In_opt_ LPCTSTR               lpName);

	HANDLE HOpenFileMapping(
		_In_ DWORD   dwDesiredAccess,
		_In_ BOOL    bInheritHandle,
		_In_ LPCTSTR lpName);

	BOOL HCloseHandle(_In_ HANDLE hObject);

	BOOL HUnmapViewOfFile(_In_ LPCVOID lpBaseAddress);

};

