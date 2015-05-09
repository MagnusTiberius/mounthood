#include "Inode.h"


Inode::Inode()
{
	superBlock.SetFileName(SYSDB);
	superBlock.Load();
	dwINodeStartAddress = superBlock.GetINodeStartAddress();
	dwINodeAreaSize = superBlock.GetINodeAreaSize();

	bitmapInode.SetFileName(SYSDB);
	DWORD addr = superBlock.GetINodeBitmapStartAddress();
	bitmapInode.SetStartAddress(addr);
	DWORD siz = superBlock.GetINodeBitmapAreaSize();
	bitmapInode.SetBitmapSize(siz);
	bitmapInode.Load();

	bitmapHeap.SetFileName(SYSDB);
	addr = superBlock.GetHeapStartAddress();
	bitmapHeap.SetStartAddress(addr);
	siz = superBlock.GetHeapSize();
	bitmapHeap.SetBitmapSize(siz);
	bitmapHeap.Load();
}


Inode::~Inode()
{
}


bool Inode::Reserve(DWORD dwSizeInBytes, Inode::LPINODE lpInode)
{
	DWORD dwBlocks = (dwSizeInBytes / 4096) + 1;
	DWORD dwIndex = bitmapHeap.FindAddressBlockToReserve(dwBlocks);
	DWORD dwValidBlockCount = bitmapHeap.ReserveBlock(dwIndex, dwBlocks);
	bitmapHeap.Save();

	DWORD dwIndex2 = bitmapInode.FindAddressBlockToReserve(1);
	DWORD dwValidBlockCount2 = bitmapInode.ReserveBlock(dwIndex2, 1);
	bitmapInode.Save();

	lpInode->dwStartBitmapHeapAddress = dwIndex;
	lpInode->dwStartBitmapHeapReserveCount = dwValidBlockCount;
	lpInode->dwStartInodeBitmapAddress = dwIndex2;

	return true;
}