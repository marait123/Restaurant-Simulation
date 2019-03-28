#pragma once
#ifndef _Vector
#define _Vector

template<typename Type>
class Vector
{
protected:
	Type** myArr;  // this is the vectors storage 
	int capacity;	// defines the capacity of the vector 
	int top;		// this is the index of the last element when full it is = capacity - 1
	int topActive;	// this variable holds the index of the last idle element

	
	// utility functions 
	///<summary>this function just increases the capacity of the vector by 20 </summary>
		int getNewCapacity();
public:
	Vector();
	virtual ~Vector();
	/**
	/*summary: this function inserts the item in the vector at the end of it
	*/
	void insert(Type);
	bool isEmpty();
	bool isFull();
	int getCapacity();
	/**
	/*summary: this function gets the index of an item equal to the item sent
	/*return: index >=0 if found and -1 if not found
	*/
	int getIndexOf(Type item);
	/**
	/*pre: you must ensure that you have the == operator overloaded for the remove funtion toworkwith your object
	/*summary: this function removes the item supplied from the vector by shifting it with all the subsequent items
	*/
	bool removeByShift(Type );
	/**
	/*pre: you must ensure that you have the == operator overloaded for the remove funtion toworkwith your object
	/*summary: this function removes the item supplied from the vector by swaping it with last element
	*/
	bool fastRemove(Type );
	///<summary>you must ensure that you have the == operator overloaded for the remove funtion to work with your object</summary>
	bool contains(Type); // No
	///<summary>this function just returns the size of the vector don't confuse with capacity</summary>
	int getSize();
	Type& operator[](int);
};

#include"Vector.cpp"

#endif // !_Vector

