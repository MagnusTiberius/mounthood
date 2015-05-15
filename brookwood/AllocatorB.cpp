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
	lpNode->bitmap = (char*)malloc(lpNode->bitmap_count);
	memset(lpNode->bitmap, 0, lpNode->bitmap_count);
	lpNode->next = NULL;
	lpNode->prev = NULL;
	lpNode->allocated = 0;
	lpNode->node_id = ctr++;
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

void* &AllocatorB::operator[](int index)
{
	void* item = NULL;
	int running_bitmap_count = 0;
	LPNODE node = lpRootHeap;
	while (node != NULL)
	{
		if (index >= running_bitmap_count)
		{
			if (index < running_bitmap_count + node->bitmap_count)
			{
				item = node->heap_block + (index * m_grain_size);
				return item;
			}
		}
		running_bitmap_count += node->bitmap_count;
		node = node->next;
	}
	return item;
}