#pragma once
#include "stdafx.h"

#include "FileSemantic.h"

#define FILE_MAP_START 138240

class DECL_API FileController : public FileSemantic
{
public:
	FileController();
	~FileController();

	VOID Create(_In_ LPCTSTR lpFileName, _In_ DWORD nBufferSize);
	DWORD CreateByGranularity(_In_ LPCTSTR lpFileName, _In_ DWORD multiplier);
	HANDLE Open(_In_ LPCTSTR lpFileName);
	VOID Write(_In_ LPCVOID lpBuffer, _In_ DWORD len);
	VOID Write(_In_ LPCVOID lpBuffer, _In_ DWORD len, _In_ DWORD dwStartAddress);
	DWORD Read(_Inout_ LPVOID lpBuffer, _In_ DWORD len, _In_ DWORD dwStartAddress);
	BOOL Close();

protected:
	HFILE hf;

	HANDLE hFile;
	SYSTEM_INFO SysInfo;
	DWORD dwSysGran;
	DWORD dwFileMapStart;
	DWORD dBytesWritten;
	int i;
};

