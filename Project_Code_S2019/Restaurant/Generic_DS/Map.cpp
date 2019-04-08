#include "Map.h"

template<typename T, typename D>
Map<T,D>::Map()
{
	this->count = 0;
	this->root = NULL;
}

template<typename T, typename D>
Map<T, D>::Map(const Map & mp)
{
	// this constructor will have to traverse the entire map to add each element in the supplied map to the current one 
	// using the breadth first traversal algorithm i will traverse the  map supplied and insert each element in it to this map
	this->count = mp.count;
	queue<MapPair<T, D>*> qMP;
	MapPair<T, D>* scan = mp.root;

	while (scan != NULL)
	{
		this->Insert(*scan);

		if (scan->GetLeftChild() != NULL) {
			qMP.push(scan->GetLeftChild());
		}

		if (scan->GetRightChild() != NULL) {
			qMP.push(scan->GetRightChild());
		}

		if (qMP.empty()) {
			break;
		}
		else
		{
			scan = qMP.front();
			qMP.pop();
		}

	}
}


template<typename T, typename D>
Map<T, D>::~Map()
{

	// traverse the whole map and delete all the MapPairs
	queue<MapPair<T, D>*> qMP;
	MapPair<T, D>* scan = this->root;

	while (scan != NULL)
	{

		if (scan->GetLeftChild() != NULL) {
			qMP.push(scan->GetLeftChild());
		}

		if (scan->GetRightChild() != NULL) {
			qMP.push(scan->GetRightChild());
		}

		delete scan;

		if (qMP.empty()) {
			break;
		}
		else
		{
			scan = qMP.front();
			qMP.pop();
		}

	}




}

template<typename T, typename D>
void Map<T, D>::Insert(MapPair<T, D> MP)
{
	this->count++;
	MapPair<T, D>* newPair = new MapPair<T, D>(MP.GetKey(), MP.GetValue());
	MapPair<T, D>** scan = &this->root;
	

	while (*scan != NULL) {

		if (MP.GetKey() < (*scan)->GetKey() ) {
			scan = &(*scan)->GetLeftChild();
		}
		else if (MP.GetKey() > (*scan)->GetKey())
		{
			scan = &(*scan)->GetRightChild();
		}
		else
		{
			throw new exception("sorry the key you have just entered is already there in the map");
		}
	}
	*scan = new MapPair<T, D>(MP.GetKey(),MP.GetValue());
}

template<typename T, typename D>
D Map<T, D>::operator[](T index)
{
	MapPair<T, D>* scan = this->root;

	if (scan == NULL) {
		throw exception("the map doesn't contain an element with that index");
	}

	while (scan != NULL) {

		if (index < scan->GetKey()) {
					scan = scan->GetLeftChild();
		}
		else if (index > scan->GetKey())
		{
			scan = scan->GetRightChild();

		}
		else
		{
			return scan->GetValue();
		}
	}

	throw exception("the map doesn't contain an element with that index");

}

template<typename T, typename D>
D Map<T, D>::At(T index)
{
	MapPair<T, D>* scan = this->root;

	if (scan == NULL) {
		throw exception("the map doesn't contain an element with that index");
	}

	while (scan != NULL) {

		if (index < scan->GetKey()) {
			scan = scan->GetLeftChild();
		}
		else if (index > scan->GetKey())
		{
			scan = scan->GetRightChild();

		}
		else
		{
			return scan->GetValue();
		}
	}

	throw exception("the map doesn't contain an element with that index");

}

template<typename T, typename D>
bool Map<T, D>::Contains(T k)
{

	MapPair<T, D>* scan = this->root;

	if (scan == NULL) {
		throw exception("the map doesn't contain an element with that index");
	}

	while (scan != NULL) {

		if (k < scan->GetKey()) {
			scan = scan->GetLeftChild();
		}
		else if (k > scan->GetKey())
		{
			scan = scan->GetRightChild();

		}
		else
		{
			return true;
		}
	}

	return false;

}

template<typename T, typename D>
int Map<T, D>::GetCount()
{
	return 0;
}

template<typename T, typename D>
bool Map<T, D>::Remove(T val)
{
	MapPair<T, D>* temp = Delete(this->root, val);
	return temp == NULL;
}

// return value is the new root 
template<typename T, typename D>
MapPair<T, D>* Map<T, D>::Delete(MapPair<T, D>* roo, const T& val)
{
	// first traverse untill you find it 
	if(roo == NULL)	return NULL; // haven't been found

	if (val < roo->GetKey()) {
		roo->SetLeftChild(Delete(roo->GetLeftChild(),val));
	}
	else if (val > roo->GetKey())
	{
		roo->SetRighttChild(Delete(roo->GetRightChild(), val));
	}
	// here you are i have found it 
	else
	{
		// if it is a leaf node
		if (roo->GetLeftChild() == NULL && roo->GetRightChild() == NULL) {
			delete roo;
			roo = NULL;
		}
		// if it has only one child 

		//if this child is the left one
		else if (roo->GetLeftChild() != NULL && roo->GetRightChild() == NULL)
		{
			MapPair<T, D>* temp = roo->GetLeftChild();
			delete roo;
			roo = temp;
		}
		
		//if this child is the right one
		else if (roo->GetRightChild() != NULL && roo->GetLeftChild() == NULL)
		{
			MapPair<T, D>* temp = roo->GetRightChild();
			delete roo;
			roo = temp;

		}
		// if it is a general node the one that has tow children
		else
		{
			MapPair<T, D>* temp = this->GetMin(roo->GetRightChild());

			roo->SetValue(temp->GetValue());
			roo->SetKey(temp->GetKey());
			
			// remove the key from the right subtree
			roo->SetRighttChild(this->Delete(roo->GetRightChild(), temp->GetKey()));
		}
	}
	return roo;
}

template<typename T, typename D>
MapPair<T, D>* Map<T, D>::GetMin(MapPair<T, D> *MP)
{
	MapPair<T, D>* scan = MP;

	while (scan != NULL) {
	
		if (scan->GetLeftChild() != NULL) {
			scan = scan->GetLeftChild();
		}
		else
		{
			break;
		}
	}

	return scan;
}
