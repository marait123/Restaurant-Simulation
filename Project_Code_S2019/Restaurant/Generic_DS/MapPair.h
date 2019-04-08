#pragma once
#include<string>
template<typename T, typename D>
class MapPair
{
protected:
	T key;
	D value;
	MapPair<T, D>* leftChild;
	MapPair<T, D>* rightChild;

public:
	MapPair();
	MapPair(T, D);
	

	~MapPair();
	T GetKey();
	D GetValue();

	void SetKey(T k);
	void SetValue(D val);

	MapPair<T, D>*& GetLeftChild();
	MapPair<T, D>*& GetRightChild();

	void SetLeftChild(MapPair<T, D>*);
	void SetRighttChild(MapPair<T, D>*);


};

#include"MapPair.cpp"