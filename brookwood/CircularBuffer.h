#pragma once
#include "stdafx.h"

template<class T>
class CircularBuffer
{
public:
	template<class T> 
	CircularBuffer() {}
	
	~CircularBuffer() {}


	VOID Push(_In_ T item)
	{
		list.push_back(item);
	}

	VOID Pop(_Out_ T *item)
	{
		item = &list[0];
		list.pop_front();
	}

private:
	std::deque<T> list;
};

