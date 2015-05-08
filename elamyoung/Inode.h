#pragma once
#include "stdafx.h"

class Inode
{
public:
	Inode();
	~Inode();

	enum INODETYPE {
		INODETYPE_UNDEFINED = 0,
		INODETYPE_SYSTABLE = 1,
		INODETYPE_TABLE = 2,
		INODETYPE_INDEX = 4,
		INODETYPE_TABLEDEF = 8,
		INODETYPE_INDEXDEF = 16,
	};

	// An INode is 256 bytes long.
	typedef struct INode_s {
		INODETYPE enInodeType;
		DWORD dwStartAddress;
		DWORD dwBlockCount;
		DWORD bIsLocked;
		DWORD dwReaderCount;
		DWORD dwWriterWaitingFlag;
	} INODE, *LPINODE;

private:

	LPINODE lpInodes;

};

