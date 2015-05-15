#include "ArrayGrowable.h"


ArrayGrowable::ArrayGrowable()
{
}


ArrayGrowable::~ArrayGrowable()
{
}

void ArrayGrowable::InitArray(size_t elementSize) {
	a = (Array*)malloc(sizeof(Array));
	memset(a, 0, sizeof(Array));

	a->size = GROWTHINCREMENT;
	size_t initialSize = a->size * elementSize;
	a->array = (char *)malloc(initialSize);
	memset(a->array, 0, initialSize);
	a->used = 0;
	a->elemSize = elementSize;
}

void ArrayGrowable::PushBack(void* element) {
	if (a->used >= a->size) {
		a->size += GROWTHINCREMENT;
		a->array = (char *)realloc(a->array, a->size * a->elemSize);
	}
	auto arrelem = a->array + (a->used * a->elemSize);
	a->used++;
	memcpy_s(arrelem, a->elemSize, element, a->elemSize);
}


void* &ArrayGrowable::operator[](int index)
{
	//auto elem = a->array + (index * a->elemSize);
	auto elem = (void*)&a->array[index * a->elemSize];
	return elem;
}

void ArrayGrowable::FreeArray() {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
	a->elemSize = 0;
}