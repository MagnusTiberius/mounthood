#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "assert.h"

#define BLOCKSIZ 4096


class Allocator
{
public:
	Allocator(_In_ DWORD dwElementSize);
	~Allocator();

	void* Next();
	bool Free(_In_ DWORD index);

	void ExpandHeap();

	void ExpandBitmap();

private:
	char *heap;
	char *bitmap;
	DWORD dwBitmapCount;
	DWORD dwGrainSize;
	DWORD dwHeapSize;

};


