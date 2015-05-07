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

	void InitHeader()
	{
		size_t siz = 8;
		HEADER_INFO info;     
		memcpy_s(info.id, 8, "SYSTEMDB", siz);
		info.num = (DWORD)0xFFFFFFFF;

		BYTE *buf = (BYTE*)malloc(sizeof(HEADER_INFO));
		size_t siz2 = sizeof(HEADER_INFO);
		memcpy_s(buf, siz2, (void*)&info, siz2);
		fileController.Open(SYSDB);
		fileController.Write((LPCVOID)buf, siz2);
		fileController.Close();
	}

private:
	FileController fileController;
	HANDLE hFile;
};

