#pragma once
#include"BDPair.h"
#include<queue>
#include"Queue.h"

///it stands for binary search doubly linked list
///k stands for key and D stands for Data or Value
/*		example on how to use the BSDLL data structure:
		{
		b.Insert(BDPair<string,double>("zaki",4));
		BDPair<string,double> BDP;
		b.peak(BDP);
		b.Deque();
		cout<<BDP.GetData()<<BDP.GetKey()<<endl;
		}*/
template<typename K, typename D>
class BSDLL
{

protected:
	BDPair<K,D>* root;
	BDPair<K,D>* head;
	BDPair<K,D>* tail;

	int count;

	/*this section is for utility functions*/
	BDPair<K,D>* Delete(BDPair<K,D>*&, const K&);
	///<summary>it returns the minimum value in the true whose root is supplied to it</summary>
	///<summary>it is designed to help in the Remove function</summary>
	///<param name = "MP">this is the pointer to right child of the node when you try to remove</param>
	BDPair<K,D> * GetMin(BDPair<K,D>* MP);

public:
	BSDLL();
	BSDLL(const BSDLL&);
	~BSDLL();
	void Insert(BDPair<K,D>);
	D operator[](K);
	D At(K);
	bool Contains(K);
	int GetCount();

	bool IsEmpty();

	bool Remove(K);
	bool peak(BDPair<K,D>& );
	bool Deque();

};

#include"BSDLL.cpp"