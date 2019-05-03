
#include "BSDLL.h"

template<typename K, typename D>
BSDLL<K,D>::BSDLL()
{
	this->count = 0;
	this->root = NULL;
	this->head = NULL;
	this->tail = NULL;

}


/*
	operations used in queue
	1. push
	2. pop
	3.front
	4.empty
	Queue
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;	
	int GetCount();

*/
template<typename K, typename D>
BSDLL<K,D>::BSDLL(const BSDLL<K,D> & mp)
{
	// this constructor will have to traverse the entire BSDLL to add each element in the supplied BSDLL to the current one 
	// using the breadth first traversal algorithm i will traverse the  BSDLL supplied and insert each element in it to this BSDLL
	
	
	this->count = 0;
	this->root = NULL;
	this->head = NULL;
	this->tail = NULL;

	/*{if (mp.IsEmpty()) return;
	this->count = mp.count; }*/

	Queue<BDPair<K, D>*> qMP;

	BDPair<K, D>* scan = mp.head;
	while (scan != NULL) {

		BDPair<K, D>* temp = new BDPair<K, D>();
		temp->SetData(scan->GetData());
		temp->SetKey(scan->GetKey());
		this->Insert(*temp);
		scan = scan->GetNext();
	}

	/*
	BDPair<K,D>* scan = mp.root;

	qMP.enqueue(mp.root);

	while (qMP.isEmpty())
	{
	qMP.dequeue(scan);

	BDPair<K, D>* temp = new BDPair<K, D>();
	temp->SetData(scan->GetData());
	temp->SetKey(scan->GetKey());

	this->Insert(*temp);

	if (scan->GetLeftChild() != NULL) {
	qMP.enqueue(scan->GetLeftChild());
	}

	if (scan->GetRightChild() != NULL) {
	qMP.enqueue(scan->GetRightChild());
	}
	}
	*/



}

template<typename K, typename D>
BSDLL<K,D>::~BSDLL()
{

	// traverse the whole BSDLL and delete all the BDPair<K,D>s
	Queue<BDPair<K,D>*> qMP;
	BDPair<K,D>* scan = this->root;
	while (scan != NULL)
	{

		if (scan->GetLeftChild() != NULL) {
			qMP.enqueue(scan->GetLeftChild());
		}

		if (scan->GetRightChild() != NULL) {
			qMP.enqueue(scan->GetRightChild());
		}

		delete scan;

		if (qMP.isEmpty()) {
			break;
		}
		else
		{
			qMP.peekFront(scan);
			qMP.dequeue(scan);
		}

	}
}

template<typename K, typename D>
/*working on it*/ /// partial done not tested
void BSDLL<K,D>::Insert(BDPair<K,D> MP)
{
	this->count++;

	BDPair<K,D>* newPair = new BDPair<K,D>(MP.GetKey(), MP.GetData());
	BDPair<K,D>** scan = &this->root;

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
			throw new exception("sorry the key you have just entered is already there in the BSDLL");
		}
	}
	*scan = new BDPair<K,D>(MP.GetKey(),MP.GetData());
	
	// handling the doubly linked list staffs
	if(tail == NULL){
		tail = *scan;
		head = tail;
	}
	else
	{
		(*scan)->SetPrev(tail);
		tail->SetNext(*scan);
		tail = *scan;
	}

}

template<typename K, typename D>
D BSDLL<K,D>::operator[](K index)
{
	BDPair<K,D>* scan = this->root;

	if (scan == NULL) {
		throw exception("the BSDLL doesn't contain an element with that index");
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
			return scan->GetData();
		}
	}

	throw exception("the BSDLL doesn't contain an element with that index");

}

template<typename K, typename D>
D BSDLL<K,D>::At(K index)
{
	BDPair<K,D>* scan = this->root;

	if (scan == NULL) {
		throw exception("the BSDLL doesn't contain an element with that index");
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
			return scan->GetData();
		}
	}

	throw exception("the BSDLL doesn't contain an element with that index");

}

template<typename K, typename D>
bool BSDLL<K,D>::Contains(K k)
{

	BDPair<K,D>* scan = this->root;

	if (scan == NULL) {
		throw exception("the BSDLL doesn't contain an element with that index");
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

template<typename K, typename D>
int BSDLL<K,D>::GetCount()
{
	return this->count;
}

template<typename K, typename D>
bool BSDLL<K,D>::IsEmpty(){
	return head == NULL;
}

/// this function doesn't distinguish not found and the one and the NULL
template<typename K, typename D>
bool BSDLL<K,D>::Remove(K val)
{
	bool isThere = this->Contains(val);
	if(isThere){
	BDPair<K,D>* temp = Delete(this->root, val);			
	}
	if(isThere)
		this->count--;

	return isThere;
}

// return value is the new root		//under construcion
// the new data structure will fail unless you find a way to delete the node from the binary tree without swapping the values
template<typename K, typename D>
BDPair<K,D>* BSDLL<K,D>::Delete(BDPair<K,D>*& roo, const K& val)
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
		/*the DLL part*/
		// if this node is a leaf node
		if (roo->GetLeftChild() == NULL && roo->GetRightChild() == NULL) {
			
			if(tail == roo){ // if i am trying to delete the one pointed to by tail
					tail= roo->GetPrev();
				}

			if(roo == this->head){
				
				head = roo->GetNext();
				if(head!=NULL)
				head->SetPrev(NULL);
				}

			else
			{
				BDPair<K,D>* temp = roo->GetPrev();
				temp->SetNext(roo->GetNext());
				if(roo->GetNext() != NULL){		// if it is the last element in the DLL		
				roo->GetNext()->SetPrev(temp);
				}
			}

		// if it is a leaf node
			delete roo;
			roo = NULL;
		}
		// if it has only one child 

		//if this child is the left one
		else if (roo->GetLeftChild() != NULL && roo->GetRightChild() == NULL)
		{
			/*the DLL part*/
			if(tail == roo){ // if i am trying to delete the one pointed to by tail
					tail= roo->GetPrev();
				}

			if(roo == this->head){
			
				head = roo->GetNext();
				head->SetPrev(NULL);
			}
			else
			{
				BDPair<K,D>* temp = roo->GetPrev();
				temp->SetNext(roo->GetNext());
				if(roo->GetNext() != NULL){		// if it is the last element in the DLL		
				roo->GetNext()->SetPrev(temp);
				}
			}
			BDPair<K,D>* temp = roo->GetLeftChild();
			delete roo;
			roo = temp;
		}
		
		//if this child is the right one
		else if (roo->GetRightChild() != NULL && roo->GetLeftChild() == NULL)
		{
			/*the DLL part*/
			if(tail == roo){ // if i am trying to delete the one pointed to by tail
					tail= roo->GetPrev();
				}		

			if(roo == this->head){
			
				head = roo->GetNext();
				head->SetPrev(NULL);
			}
			else
			{
				BDPair<K,D>* temp = roo->GetPrev();
				temp->SetNext(roo->GetNext());
				if(roo->GetNext() != NULL){		// if it is the last element in the DLL		
				roo->GetNext()->SetPrev(temp);
				}
			}

			BDPair<K,D>* temp = roo->GetRightChild();
			delete roo;
			roo = temp;

		}
		// if it is a general node the one that has tow children
		else
		{
			BDPair<K,D>* temp = this->GetMin(roo->GetRightChild());
			// handling the DLL linked list rearrangement to compensate for the data swapping
			// the following swapping is doesn't affect the Binary search tree properties

			if(roo == head){
				head = roo->GetNext();
			} // special case

			temp->GetPrev()->SetNext(roo);
			roo->GetNext()->SetPrev(roo->GetPrev());
			roo->SetPrev(temp->GetPrev());
			roo->SetNext(temp);
			temp->SetPrev(roo);

			roo->SetData(temp->GetData());
			roo->SetKey(temp->GetKey());
			
			// remove the key from the right subtree
			roo->SetRighttChild(this->Delete(roo->GetRightChild(), temp->GetKey()));
		}
	}
	return roo;
}

template<typename K, typename D>
BDPair<K,D>* BSDLL<K,D>::GetMin(BDPair<K,D> *MP)
{
	BDPair<K,D>* scan = MP;

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

template<typename K, typename D>
bool BSDLL<K,D>::peak(BDPair<K,D>& BP){

	if(head == NULL){
		return false;
	}
	BP = *head;
	return true;
}

template<typename K, typename D>
bool BSDLL<K,D>::Deque(){
	if(head == NULL)
		return false;
	this->Remove(head->GetKey());
	return true;
}

