#pragma once

template <typename T>
class PriorityQ_ADT
{
public:
	virtual void _sortNode(int i = 0) = 0;
	virtual void _resort() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool enqueue(const T& newEntry) = 0;
	virtual bool dequeue(T& frntEntry) = 0;
	virtual bool peekFront(T& frntEntry) const = 0;
};