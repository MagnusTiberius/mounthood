#include "Allocator.h"
#include "assert.h"


Allocator::Allocator(DWORD dwElementSize)
{
	assert(BLOCKSIZ > dwElementSize);
	dwHeapSize = BLOCKSIZ;
	heap = (char*)malloc(BLOCKSIZ);
	dwBitmapCount = (BLOCKSIZ / dwElementSize);
	bitmap = (char*)malloc(dwBitmapCount);

	memset(heap, 0, BLOCKSIZ);
	memset(bitmap, 0, dwBitmapCount);
	dwGrainSize = dwElementSize;
}


Allocator::~Allocator()
{
	heap = (char*)realloc(heap, 0);
	free(heap);
	free(bitmap);
}

void* Allocator::Next()
{
	void *item;
	for (int i = 0; i < (int)(dwHeapSize / dwGrainSize); i++)
	{
		if (bitmap[i] == 0)
		{
			bitmap[i] = 1;
			item = (void*)(heap + (i * dwGrainSize));
			return item;
		}
	}
	ExpandBitmap();
	ExpandHeap();
	return Next();
}

bool Allocator::Free(DWORD index)
{
	assert(dwBitmapCount > index);
	bool rv = false;
	bitmap[index] = 0;
	int displacement = index * dwGrainSize;
	char *memloc = heap + displacement;
	memset(memloc, 0, dwGrainSize);
	return rv;
}

void Allocator::ExpandHeap()
{
	auto ptrHeap = heap + dwHeapSize;
	DWORD dwOldHeapSize = dwHeapSize;
	dwHeapSize = dwHeapSize + BLOCKSIZ;
	heap = (char*)realloc((void*)heap, (size_t)dwHeapSize);
	memset(ptrHeap, 0, BLOCKSIZ);
	dwBitmapCount = (dwHeapSize / dwGrainSize);
}

void Allocator::ExpandBitmap()
{
	char *ptr = bitmap + dwBitmapCount;
	DWORD delta = (BLOCKSIZ / dwGrainSize);
	DWORD dwoldBitmapCount = dwBitmapCount;
	DWORD dwNewBitmapCount = dwoldBitmapCount + delta;
	bitmap = (char*)realloc((void*)bitmap, (size_t)(dwNewBitmapCount));
	memset(ptr, 0, (size_t)delta);
	dwBitmapCount = dwNewBitmapCount;
	return;
}