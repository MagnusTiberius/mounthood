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
		int node_id;
		char* heap_block;
		struct node *prev;
		struct node *next;
		size_t allocated;
		char *bitmap;
		size_t bitmap_count;
	}NODE, *LPNODE;


	void* Reserve();
	void* &operator[](int index);

private:
	void* AllocFromNode(LPNODE lpNode, size_t size);
	void Add(LPNODE lpNode);
	LPNODE New();

private:
	LPNODE lpRootHeap;
	LPNODE lpBackHeap;
	size_t m_grain_size;
	size_t index;
	size_t count_per_node;
	int ctr = 0;
};

