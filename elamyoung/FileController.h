#pragma once
#include "stdafx.h"

#include "FileSemantic.h"

#define FILE_MAP_START 138240

class DECL_API FileController : public FileSemantic
{
public:
	FileController();
	~FileController();

	void Init(_In_ LPCTSTR lpFileName, _In_ INT nBufferSize)
	{
		hFile = HCreateFile(lpFileName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		GetSystemInfo(&SysInfo);
		dwSysGran = SysInfo.dwAllocationGranularity;
		
		CHAR *buffer = (CHAR*)malloc(nBufferSize);
		memset(buffer, 32, nBufferSize);

		//for (i = 0; i<nBufferSize; i++)
		//{
		//	WriteFile(hFile, buffer, nBufferSize, &dBytesWritten, NULL);
		//}
		WriteFile(hFile, buffer, nBufferSize, &dBytesWritten, NULL);

		CloseHandle(hFile);

	}

	HANDLE Open(_In_ LPCTSTR lpFileName)
	{
		hFile = HCreateFile(lpFileName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		return hFile;
	}

	void Write(_In_ LPCVOID lpBuffer, _In_ DWORD len)
	{
		DWORD dwWritten;
		BOOL b = HWriteFile(hFile, lpBuffer, len, &dwWritten, NULL);
	}

	BOOL Close()
	{
		return ::CloseHandle(hFile);
	}

protected:
	HFILE hf;

	HANDLE hFile;
	SYSTEM_INFO SysInfo;
	DWORD dwSysGran;
	DWORD dwFileMapStart;
	DWORD dBytesWritten;
	int i;
};

