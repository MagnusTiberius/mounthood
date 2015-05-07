#pragma once

#include "FileController.h"

#define SYSDB L"SystemDB.dat"

class DECL_API SystemDB
{
public:
	SystemDB();
	~SystemDB();

	typedef struct HeaderInfo {
		CHAR id[8];
		DWORD num;
	} HEADER_INFO, LPHEADER_INFO;

	void InitSystem();
	void OpenSystemDB();

	void InitHeader();

private:
	FileController fileController;
	HANDLE hFile;
};

