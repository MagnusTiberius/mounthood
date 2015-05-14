#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "assert.h"


#define BLOCKSIZE 4096

class AllocatorB
{
public:
	AllocatorB(size_t item_size);
	~AllocatorB();

	typedef struct node {
		char* heap_block;
		struct node *prev;
		struct node *next;
		size_t allocated;
		char *bitmap;
		size_t bitmap_count;
	}NODE, *LPNODE;


	void* reserve(size_t size)
	{
		return alloc_from_node(lpRootHeap, size);
	}

private:
	void* alloc_from_node(LPNODE lpNode, size_t size)
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
			return alloc_from_node(lpNode->next, size);
		}
		if (lpNode->next == NULL)
		{
			LPNODE new_node = New();
			Add(new_node);
			return alloc_from_node(new_node, size);
		}
	}

private:
	void Add(LPNODE lpNode)
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

	LPNODE New()
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
		return lpNode;

	}

private:
	LPNODE lpRootHeap;
	LPNODE lpBackHeap;
	size_t m_grain_size;
	size_t index;
};

