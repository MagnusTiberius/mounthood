#pragma once
#include "stdafx.h"

#include "FileSemantic.h"

#define FILE_MAP_START 138240

class DECL_API FileController : public FileSemantic
{
public:
	FileController();
	~FileController();

	void Init(_In_ LPCTSTR lpFileName, _In_ INT nBufferSize);
	HANDLE Open(_In_ LPCTSTR lpFileName);
	void Write(_In_ LPCVOID lpBuffer, _In_ DWORD len);
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

