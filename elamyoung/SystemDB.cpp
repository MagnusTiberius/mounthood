#include "stdafx.h"
#include "SystemDB.h"


SystemDB::SystemDB()
{
}


SystemDB::~SystemDB()
{
}

void SystemDB::InitSystem()
{
	dwSizeSystemDB = fileController.CreateByGranularity(SYSDB, 256);
	superBlock.Init(dwSizeSystemDB);
}

void SystemDB::OpenSystemDB()
{
	fileController.Open(SYSDB);
}

// testing
void SystemDB::InitHeader()
{
	size_t siz = 8;
	HEADER_INFO info;
	memcpy_s(info.id, siz, "SYSTEMDB", siz);
	info.num = (DWORD)0xFFFFFFFF;

	BYTE *buf = (BYTE*)malloc(sizeof(HEADER_INFO));
	size_t siz2 = sizeof(HEADER_INFO);
	memcpy_s(buf, siz2, (void*)&info, siz2);
	fileController.Open(SYSDB);
	fileController.Write((LPCVOID)buf, siz2);
	fileController.Close();
	free(buf);
}