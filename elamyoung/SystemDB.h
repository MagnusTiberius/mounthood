#pragma once

#include "FileController.h"
#include "SuperBlock.h"



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
	DWORD SetSizeByGranularity(_In_ DWORD multiplier);

private:
	SYSTEM_INFO SysInfo;
	FileController fileController;
	HANDLE hFile;
	DWORD dwSizeSystemDB;
	DWORD dwSysGran;
	SuperBlock superBlock;

};

