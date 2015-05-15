#pragma once
#include <Windows.h>

#define GROWTHINCREMENT 10

class ArrayGrowable
{
public:
	ArrayGrowable();
	~ArrayGrowable();


	void InitArray(size_t elementSize) {
		a = (Array*)malloc(sizeof(Array));
		memset(a, 0, sizeof(Array));

		a->size = GROWTHINCREMENT;
		size_t initialSize = a->size * elementSize;
		a->array = (char *)malloc(initialSize);
		memset(a->array, 0, initialSize);
		a->used = 0;
		a->elemSize = elementSize;
	}

	void PushBack(void* element) {
		if (a->used >= a->size) {
			a->size += GROWTHINCREMENT;
			a->array = (char *)realloc(a->array, a->size * a->elemSize);
		}
		auto arrelem = a->array + (a->used * a->elemSize);
		a->used++;
		memcpy_s(arrelem, a->elemSize, element, a->elemSize);
	}


	void* &operator[](int index)
	{
		//auto elem = a->array + (index * a->elemSize);
		auto elem = (void*)&a->array[index * a->elemSize];
		return elem;
	}

	void FreeArray() {
		free(a->array);
		a->array = NULL;
		a->used = a->size = 0;
		a->elemSize = 0;
	}

private:
	typedef struct {
		char *array;
		size_t used;
		size_t size;
		size_t elemSize;
	} Array;

	Array *a;

};

