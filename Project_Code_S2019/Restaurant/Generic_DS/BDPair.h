#pragma once
#include<string>
using namespace std;
///it stands for binary search doubly linked list Node
template<typename K,typename D>
class BDPair
{
	

private:
	/// i will use D for the data
	D data;
	/// i will use K for key 
	K key;
	BDPair* next;
	BDPair* prev;

	/*the Map Pair part of the private memebers*/
	BDPair* leftChild;
	BDPair* rightChild;

	

public:
	BDPair();
	BDPair(BDPair&);
	BDPair& operator =(BDPair&);
	/// datA:is the data of the Pair
	BDPair(K key ,D datA,BDPair* nexT = nullptr,BDPair* preV = nullptr,BDPair* LC = nullptr,BDPair* RC= nullptr);
	~BDPair();
	
	BDPair* GetNext();
	void SetNext(BDPair*);

	BDPair* GetPrev();
	void SetPrev(BDPair*);

	K GetKey();
	void SetKey(K);


	D GetData();


	void SetData(D);
	void SetLeftChild(BDPair*);
	void SetRighttChild(BDPair*);


	BDPair*& GetLeftChild();
	BDPair*& GetRightChild();


	/*the Map Pair part of the pubic memebers*/
};

#include"BDPair.cpp"

