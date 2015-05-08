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

BOOL FileController::Close()
{
	return ::CloseHandle(hFile);
}