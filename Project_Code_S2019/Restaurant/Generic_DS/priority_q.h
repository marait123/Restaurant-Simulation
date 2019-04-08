#pragma once
#include<utility>
#include"PriorityQ_ADT.h"
#include"Pair.h"
// constexpr int MAXSIZE = 1000;
const int MAXSIZE = 1000;

template <typename T>
class priority_q : public PriorityQ_ADT<T>
{
	T data[MAXSIZE];
	int insIdx;

	//Utility function
	void _sortNode(int i = 0);
	void _resort();
	int count;
public :
	priority_q();
	~priority_q();

	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry) const;
	int	GetCount();
};

template<typename T>
inline void priority_q<T>::_sortNode(int i)
{
	//We simulate the max-heap using an array
	//Each parent node at index i has 2 children, left at 2*i+1 and right at 2*i+2
	int left = 2*i + 1;
	int right = 2*i + 2;
	int mx = i;

	//First, compare the left node with the current node to find the max
	if (left <= insIdx && data[left] > data[mx]) mx = left;
	//Then the right
	if (right <= insIdx && data[right] > data[mx]) mx = right;

	//In case the max el. is the left or the right, not i
	if (mx != i) {
		//Swap the largest with i
		std::swap(data[i], data[mx]);

		//Complete running on the new max
		_sortNode(mx);
	}
}

template<typename T>
inline void priority_q<T>::_resort()
{
	//Sorting all non-leaf nodes as a max-heap
	for (int i = insIdx / 2 - 1; i > -1; --i) {
		_sortNode(i);
	}
}


template<typename T>
inline priority_q<T>::priority_q()
{
	insIdx = 0;
	this->count = 0;
}

template<typename T>
inline priority_q<T>::~priority_q()
{
}

template<typename T>
inline bool priority_q<T>::isEmpty() const
{
	return insIdx == 0;
}

template<typename T>
inline bool priority_q<T>::enqueue(const T & newEntry)
{

	if (insIdx == MAXSIZE) return false;
	data[insIdx++] = newEntry;
	_resort();

	this->count++;
	return false;
}

template<typename T>
inline bool priority_q<T>::dequeue(T & frntEntry)
{
	if (insIdx == 0) return false;
	frntEntry = data[0];
	data[0] = data[--insIdx];
	_resort();

	this->count--;
	return true;
}

template<typename T>
inline bool priority_q<T>::peekFront(T & frntEntry) const
{
	if (insIdx == 0) return false;
	frntEntry = data[0];
	return true;
}

template<typename T>
inline int priority_q<T>::GetCount()
{
	return this->count;
}
