#include "MapPair.h"
template<typename T, typename D>
void MapPair<T,D>::SetLeftChild(MapPair * LC)
{
	this->leftChild = LC;
}

template<typename T, typename D>
void MapPair<T, D>::SetRighttChild(MapPair * RC)
{
	this->rightChild = RC;
}

template<typename T, typename D>
MapPair<T, D>*& MapPair<T, D>::GetLeftChild()
{
	return this->leftChild;
}

template<typename T, typename D>
MapPair<T, D>*& MapPair<T, D>::GetRightChild()
{
	return this->rightChild;
}

template<typename T, typename D>
MapPair<T, D>::MapPair()
{
	this->leftChild = NULL;
	this->rightChild = NULL;
	
}

template<typename T, typename D>
MapPair<T, D>::MapPair(T k , D val)
{
	this->key = k;
	this->value = val;
	this->leftChild = NULL;
	this->rightChild = NULL;
}


template<typename T, typename D>
MapPair<T, D>::~MapPair()
{
}

template<typename T, typename D>
T MapPair<T, D>::GetKey()
{
	return this->key;
}

template<typename T, typename D>
D MapPair<T, D>::GetValue()
{
	return this->value;
}

template<typename T, typename D>
void MapPair<T, D>::SetKey(T k)
{
	this->key = k;
}

template<typename T, typename D>
void MapPair<T,D>::SetValue(D val)
{
	this->value = val;
}
