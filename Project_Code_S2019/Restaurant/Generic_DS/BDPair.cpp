#include "BDPair.h"


template<typename K,typename D>
BDPair<K,D>::BDPair()
{
	this->next = NULL;
	this->leftChild = NULL;
	this->rightChild = NULL;
}

template<typename K,typename D>
BDPair<K,D>::BDPair(BDPair<K,D>& BDP){
	this->key = BDP.key;
	this->data = BDP.data;
	this->next = NULL;
	this->prev = NULL;
	this->leftChild = NULL;
	this->rightChild = NULL;

}

template<typename K,typename D>
BDPair<K,D>& BDPair<K,D>::operator=(BDPair<K,D>& BDP){
	this->key = BDP.key;
	this->data = BDP.data;
	this->next = NULL;
	this->prev = NULL;
	this->leftChild = NULL;
	this->rightChild = NULL;
	return *this;
}

template<typename K,typename D>
BDPair<K,D>::~BDPair()
{
}

template<typename K,typename D>
BDPair<K,D>::BDPair(	K keY 
			   ,D datA
			   ,BDPair<K,D>* nexT
			   ,BDPair<K,D>* preV
			   ,BDPair<K,D>* LC 
			   ,BDPair<K,D>* RC)
{
	this->key = keY;
	this->data = datA;
	this->next = nexT;
	this->prev = preV;
	this->leftChild = LC;
	this->rightChild = RC;

}


template<typename K,typename D>
D BDPair<K,D>::GetData(){
	return this->data;
}

template<typename K,typename D>
void BDPair<K,D>::SetData(D datA){
	this->data = datA;
}

template<typename K,typename D>
K BDPair<K,D>::GetKey(){
	return this->key;
}

template<typename K,typename D>
void BDPair<K,D>::SetKey(K keY){
	this->key = keY;
}


	/*Begin: Doubly Linked List functions*/

template<typename K,typename D>
BDPair<K,D>* BDPair<K,D>::GetNext(){

	return this->next;

}

template<typename K,typename D>
void BDPair<K,D>::SetNext(BDPair* nexT){
	this->next = nexT;
}

template<typename K,typename D>
BDPair<K,D>* BDPair<K,D>::GetPrev(){
	return this->prev;
}

template<typename K,typename D>
void BDPair<K,D>::SetPrev(BDPair* preV){
	this->prev = preV;
}


	/*End: Doubly Linked List functions*/

	/*Begin: Map functions*/


template<typename K,typename D>
void BDPair<K,D>::SetLeftChild(BDPair<K,D> * LC)
{
	this->leftChild = LC;
}

template<typename K,typename D>
void BDPair<K,D>::SetRighttChild(BDPair<K,D> * RC)
{
	this->rightChild = RC;
}

template<typename K,typename D>
BDPair<K,D>*& BDPair<K,D>::GetLeftChild()
{
	return this->leftChild;
}

template<typename K,typename D>
BDPair<K,D>*& BDPair<K,D>::GetRightChild()
{
	return this->rightChild;
}


