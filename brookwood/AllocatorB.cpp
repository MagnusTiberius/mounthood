#include "AllocatorB.h"


AllocatorB::AllocatorB(size_t item_size)
{
	assert(BLOCKSIZE > item_size);
	count_per_node = 0;
	index = 0;
	lpRootHeap = NULL;
	lpBackHeap = NULL;
	m_grain_size = item_size;

	arrgrw.initArray(sizeof(LPNODE));

	LPNODE node = New();
	Add(node);
}


AllocatorB::~AllocatorB()
{
	LPNODE node = lpBackHeap;
	while (node->prev != NULL)
	{
		free(node->bitmap);
		node->bitmap = NULL;
		free(node->heap_block);
		node->heap_block = NULL;
		node = node->prev;
		memset(node->next, 0, sizeof(NODE));
		free(node->next);
	}
}


void AllocatorB::Add(LPNODE lpNode)
{
	if (lpRootHeap == NULL)
	{
		lpRootHeap = lpNode;
		lpBackHeap = lpNode;
		return;
	}
	lpBackHeap->next = lpNode;
	lpNode->prev = lpBackHeap;
	lpBackHeap = lpNode;
}

AllocatorB::LPNODE AllocatorB::New()
{
	LPNODE lpNode = (LPNODE)malloc(sizeof(NODE));
	memset(lpNode, 0, sizeof(NODE));
	lpNode->heap_block = (char*)malloc(BLOCKSIZE);
	memset(lpNode->heap_block, 0, BLOCKSIZE);
	lpNode->bitmap_count = (BLOCKSIZE / m_grain_size);
	count_per_node = lpNode->bitmap_count;
	lpNode->bitmap = (char*)malloc(lpNode->bitmap_count);
	memset(lpNode->bitmap, 0, lpNode->bitmap_count);
	lpNode->next = NULL;
	lpNode->prev = NULL;
	lpNode->allocated = 0;
	lpNode->node_id = ctr++;
	//DWORD addr = (DWORD)lpNode;
	//printf("lpNode: %d \n", (DWORD)lpNode);
	//printf("addr: %d \n", (DWORD)addr);
	LPNODE* ptr = &lpNode;
	arrgrw.insertArray((void*)ptr);
	return lpNode;

}

void* AllocatorB::Reserve()
{
	return AllocFromNode(lpRootHeap, m_grain_size);
}

void* AllocatorB::AllocFromNode(LPNODE lpNode, size_t size)
{
	void* item;
	int n = lpNode->bitmap_count;
	for (int i = 0; i < n; i++)
	{
		if (lpNode->bitmap[i] == 0)
		{
			lpNode->bitmap[i] = 1;
			item = lpNode->heap_block + (i * size);
			lpNode->allocated += size;
			return item;
		}
	}
	if (lpNode->next != NULL)
	{
		return AllocFromNode(lpNode->next, size);
	}
	if (lpNode->next == NULL)
	{
		LPNODE new_node = New();
		Add(new_node);
		return AllocFromNode(new_node, size);
	}
}

#define FAST0
#ifdef FAST0
void* &AllocatorB::operator[](int indexv)
{
	void* item = NULL;
	int m_index = indexv;
	int running_bitmap_count = 0;
	int node_index = m_index / count_per_node;
	LPNODE *pptr = (LPNODE*)arrgrw[node_index];
	LPNODE node = *pptr;
	running_bitmap_count = node_index * node->bitmap_count;
	m_index -= running_bitmap_count;
	item = node->heap_block + (m_index * m_grain_size);
	return item;
}
#endif


#ifdef FAST1
void* &AllocatorB::operator[](int indexv)
{
	void* item = NULL;
	int m_index = indexv;
	int running_bitmap_count = 0;
	LPNODE node = lpRootHeap;
	int node_index = m_index / count_per_node;
	while (node != NULL)
	{
		if (node->node_id == node_index)
		{
			m_index -= running_bitmap_count;
			item = node->heap_block + (m_index * m_grain_size);
			return item;
		}
		running_bitmap_count += node->bitmap_count;
		node = node->next;
	}
	return item;
}
#endif

#ifdef FAST2
void* &AllocatorB::operator[](int indexv)
{
	void* item = NULL;
	int m_index = indexv;
	int running_bitmap_count = 0;
	LPNODE node = lpRootHeap;
	while (node != NULL)
	{
		if (m_index >= running_bitmap_count)
		{
			if (m_index < running_bitmap_count + node->bitmap_count)
			{
				m_index -= running_bitmap_count;
				item = node->heap_block + (m_index * m_grain_size);
				return item;
			}
		}
		running_bitmap_count += node->bitmap_count;
		node = node->next;
	}
	return item;
}
#endif