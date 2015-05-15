#pragma once
#include <Windows.h>

#define GROWTHINCREMENT 10

class ArrayGrowable
{
public:
	ArrayGrowable();
	~ArrayGrowable();

	void InitArray(size_t elementSize);
	void PushBack(void* element);
	void* &operator[](int index);
	void FreeArray();

private:
	typedef struct {
		char *array;
		size_t used;
		size_t size;
		size_t elemSize;
	} Array;

	Array *a;

};

