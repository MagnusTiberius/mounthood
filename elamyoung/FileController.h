#pragma once
#include "stdafx.h"

#include "FileSemantic.h"


class DECL_API FileController : public FileSemantic
{
public:
	FileController();
	~FileController();

	void Init(_In_ LPCTSTR lpFileName)
	{
		hFile = HCreateFile(lpFileName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		CloseHandle(hFile);

	}

private:
	HANDLE hFile;

};

