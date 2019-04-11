#include "Vector.h"

template<typename Type>
int Vector<Type>::getNewCapacity()
{
	return capacity+20;
}
template<typename Type>
Vector<Type>::Vector()
{
	top = -1;
	capacity = 100;
	myArr = new Type*[capacity];
	for (size_t i = 0; i < capacity; i++)
	{
		myArr[i] = NULL;	// all set to null
	}


}


template<typename Type>
Vector<Type>::~Vector()
{
	for (size_t i = 0; i <= top; i++)
	{
		if(myArr[i]!=NULL)
		delete myArr[i];
	}
	//delete[] myArr;
}

template<typename Type>
void Vector<Type>::insert(Type Str)
{

	// increase by 20 if full
	if (this->isFull()) {
		int newCapa = this->getNewCapacity();
		Type** newArr = new Type*[newCapa];

		for (size_t i = 0; i < capacity; i++)
		{
			newArr[i] = myArr[i];
		}

		for (size_t i = capacity; i < newCapa; i++)
		{
			newArr[i] = NULL;
		}

		delete[] myArr;
		myArr = newArr;

	}
	myArr[++top] = new Type(Str);


}

template<typename Type>
bool Vector<Type>::isEmpty()
{
	return top < 0;  // when top == -1
}

template<typename Type>
bool Vector<Type>::isFull()
{
	return top >= capacity-1; // equality is just enough {but not harmful to use >=}
}

template<typename Type>
int Vector<Type>::getCapacity()
{
	
	return this->capacity;
}

template<typename Type>
int Vector<Type>::getIndexOf(Type item)
{
	int index = -1;
	for (size_t i = 0; i <= top; i++)
	{
		if (*myArr[i] == item) {
			return i;
		}
	}
	return index;
}
 

template<typename Type>
bool Vector<Type>::removeByShift(Type item)
{
	int index = this->getIndexOf(item);
	if (index == -1) {
		return false;
	}
	delete myArr[index];
	for (size_t i = index; i < top; i++)
	{
		myArr[i] = myArr[i + 1];
	}
	myArr[top] = NULL;
	top--;

	return true;
}

template<typename Type>
bool Vector<Type>::fastRemove(Type item)
{
	int index = getIndexOf(item);
	if (index == -1) {
		return false;
	}

	Type* temp = myArr[index];
	myArr[index] = myArr[top];
	myArr[top] = temp;

	delete myArr[top];
	myArr[top] = NULL;
	top--;
	
	return true;
}

template<typename Type>
bool Vector<Type>::RemoveByIndex(int Index)
{
	int index = Index;
	if (index <= -1) {
		return false;
	}

	Type* temp = myArr[index];
	myArr[index] = myArr[top];
	myArr[top] = temp;

	delete myArr[top];
	myArr[top] = NULL;
	top--;

	return true;
}

template<typename Type>
bool Vector<Type>::contains(Type item)
{
	return getIndexOf(item) == -1;
} 

template<typename Type>
int Vector<Type>::getSize()
{
	return top+1;
}

template<typename Type>
Type & Vector<Type>::operator[](int index)
{
	// TODO: insert return statement here
	return *myArr[index];

}
