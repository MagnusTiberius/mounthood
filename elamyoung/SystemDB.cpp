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
	fileController.Init(SYSDB, 1024);
}

void SystemDB::OpenSystemDB()
{
	fileController.Open(SYSDB);
}