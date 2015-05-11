#pragma once

#include "stdafx.h"
#include "SystemDB.h"
#include "SuperBlock.h"
#include "FileController.h"
#include "Bitmap.h"
#include "Inode.h"


class Test1
{
public:
	Test1();
	~Test1();

	void Run2()
	{

	}

	void Run1()
	{
		SystemDB systemDB;
		systemDB.InitSystem();

		//
		// Superblock testing.
		//
		SuperBlock superBlock;
		FileController fileController;
		SuperBlock::SUPERBLOCK aBlock;
		size_t n = sizeof(SuperBlock::SUPERBLOCK);
		memset(&aBlock, 0, n);
		fileController.Open(SYSDB);
		DWORD m = fileController.Read(&aBlock, n, 0);
		fileController.Close();
		//superBlock.Load();
		//
		// Superblock now created, try reading it back.
		//
		SuperBlock superBlock2;
		superBlock2.SetFileName(SYSDB);
		superBlock2.Load();
		SuperBlock::LPSUPERBLOCK aBlock2 = superBlock2.GetSuperBlock();
		//
		// INode Bitmap testing.
		//
		Bitmap bitmap;
		bitmap.SetFileName(SYSDB);
		bitmap.SetBitmapSize(aBlock.dwINodeBitmapAreaSize);
		bitmap.SetStartAddress(aBlock.dwINodeBitmapStartAddress);
		bitmap.Load();
		DWORD nSizeBitmap = bitmap.GetBitmapSize();
		DWORD dwAddress1 = bitmap.FindAddressBlockToReserve(20);
		assert(dwAddress1 == 0);
		bitmap.ReserveBlock(dwAddress1, 20);
		DWORD dwAddress2 = bitmap.FindAddressBlockToReserve(23);
		assert(dwAddress2 == 20);
		bitmap.ReserveBlock(dwAddress2, 23);
		DWORD dwAddress3 = bitmap.FindAddressBlockToReserve(23);
		assert(dwAddress3 == 43);
		bitmap.ReserveBlock(dwAddress3, 23);
		bitmap.Save();

		//
		// Test if INode bitmap got saved, load it back and reserve more blocks.
		//
		Bitmap bitmap2;
		bitmap2.SetFileName(SYSDB);
		bitmap2.SetBitmapSize(aBlock.dwINodeBitmapAreaSize);
		bitmap2.SetStartAddress(aBlock.dwINodeBitmapStartAddress);
		bitmap2.Load();
		DWORD nSizeBitmap2 = bitmap2.GetBitmapSize();
		DWORD dwAddress4 = bitmap2.FindAddressBlockToReserve(73);
		assert(dwAddress4 == 66);
		bitmap2.Save();

		//
		// Test bitmap heap. Try to reserve blocks.
		//
		Bitmap bitmapHeap;
		bitmapHeap.SetFileName(SYSDB);
		DWORD addr = superBlock2.GetHeapStartAddress();
		bitmapHeap.SetStartAddress(addr);
		DWORD siz = superBlock2.GetHeapSize();
		bitmapHeap.SetBitmapSize(siz);
		bitmapHeap.Load();

		DWORD dwSizeInBytes = 23864;
		DWORD dwBlocks = (dwSizeInBytes / 4096) + 1;
		DWORD dwIndex = bitmapHeap.FindAddressBlockToReserve(dwBlocks);
		DWORD dwValidBlockCount = bitmapHeap.ReserveBlock(dwIndex, dwBlocks);
		bitmapHeap.Save();

		//
		// Try to reserve an inode.
		//
		Inode::INODE m_inode, m_inode1, m_inode2, m_inode3;
		size_t n2 = sizeof(Inode::INODE);
		memset(&m_inode, 0, n2);
		memset(&m_inode1, 0, n2);
		memset(&m_inode2, 0, n2);
		memset(&m_inode3, 0, n2);
		Inode inode;
		inode.Reserve(43123, &m_inode);
		inode.Reserve(412456, &m_inode1);
		inode.Reserve(5876987, &m_inode2);
		inode.Reserve(8768, &m_inode3);


	}
};

