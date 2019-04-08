#pragma once
#include"MapPair.h"
#include<queue>
using namespace std;

template<typename T,typename D>
class Map
{
protected:

	MapPair<T, D>* root;
	int count;

	/*this section is for utility functions*/
	MapPair<T, D>* Delete(MapPair<T, D>*, const T&);
	///<summary>it returns the minimum value in the true whose root is supplied to it</summary>
	///<summary>it is designed to help in the Remove function</summary>
	///<param name = "MP">this is the pointer to right child of the node when you try to remove</param>
	MapPair<T, D> * GetMin(MapPair<T, D>* MP);
public:
	Map();
	Map(const Map<T, D>&);
	~Map();
	void Insert(MapPair<T, D>);
	D operator[](T);
	D At(T);
	bool Contains(T);
	int GetCount();
	bool Remove(T);
	///<summary>this is the recursive version of the delete function which is about to be transformed into iterative</summary>

	
	T testMin() {

	}

};

#include"Map.cpp"