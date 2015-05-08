#pragma once
#include "stdafx.h"

class Inode
{
public:
	Inode();
	~Inode();

	enum INODETYPE {
		INODETYPE_TABLE,
		INODETYPE_INDEX,
		INODETYPE_TABLEDEF,
		INODETYPE_INDEXDEF,
	};

	typedef struct INode_s {
		INODETYPE enInodeType;
		DWORD dwStartAddress;
		HANDLE hMutex;
	} INODE, *LPINODE;

private:

	LPINODE lpInodes;

};

