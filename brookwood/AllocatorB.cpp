#include "AllocatorB.h"


AllocatorB::AllocatorB(size_t item_size)
{
	index = 0;
	lpRootHeap = NULL;
	lpBackHeap = NULL;
	m_grain_size = item_size;
	LPNODE node = New();
	Add(node);
}


AllocatorB::~AllocatorB()
{
}
