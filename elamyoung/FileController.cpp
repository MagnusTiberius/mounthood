#include "stdafx.h"
#include "FileController.h"


FileController::FileController()
{
}


FileController::~FileController()
{
}


void FileController::Create(_In_ LPCTSTR lpFileName, _In_ DWORD nBufferSize)
{
	DWORD nFinalBufferSize;
	DWORD nBlocks;
	DWORD nValidBufferSize;
	hFile = HCreateFile(lpFileName,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	GetSystemInfo(&SysInfo);
	dwSysGran = SysInfo.dwAllocationGranularity;

	if (nBufferSize < 1000000)
	{
		nValidBufferSize = (1024 * 1024);
	}
	else
	{
		nValidBufferSize = nBufferSize;
	}

	nBlocks = (nBufferSize / dwSysGran) + 1;
	nFinalBufferSize = nBlocks * dwSysGran;

	CHAR *buffer = (CHAR*)malloc(nBufferSize);
	memset(buffer, 0, nBufferSize);

	HWriteFile(hFile, buffer, nBufferSize, &dBytesWritten, NULL);
	free(buffer);
	CloseHandle(hFile);

}

DWORD FileController::CreateByGranularity(_In_ LPCTSTR lpFileName, _In_ DWORD multiplier)
{
	GetSystemInfo(&SysInfo);
	dwSysGran = SysInfo.dwAllocationGranularity;
	DWORD totalSize = multiplier * dwSysGran;
	assert(totalSize > 0);
	Create(lpFileName, totalSize);
	return totalSize;
}

HANDLE FileController::Open(_In_ LPCTSTR lpFileName)
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

void FileController::Write(_In_ LPCVOID lpBuffer, _In_ DWORD len)
{
	DWORD dwWritten;
	BOOL b = HWriteFile(hFile, lpBuffer, len, &dwWritten, NULL);
}

void FileController::Write(_In_ LPCVOID lpBuffer, _In_ DWORD len, _In_ DWORD dwStartAddress)
{
	DWORD dwWritten;
	DWORD rv = ::SetFilePointer(hFile, dwStartAddress, NULL, FILE_BEGIN);
	BOOL b = HWriteFile(hFile, lpBuffer, len, &dwWritten, NULL);
}

DWORD FileController::Read(_Inout_ LPVOID lpBuffer, _In_ DWORD len, _In_ DWORD dwStartAddress)
{
	DWORD dwRead = 0;
	DWORD rv = ::SetFilePointer(hFile, dwStartAddress, NULL, FILE_BEGIN);
	BOOL b = ::ReadFile(hFile, lpBuffer, len, &dwRead, NULL);
	return dwRead;
}


BOOL FileController::Close()
{
	return ::CloseHandle(hFile);
}