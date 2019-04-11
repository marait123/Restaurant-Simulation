#include "CancelEvent.h"

#include"../Rest//Restaurant.h"





CancelEvent::CancelEvent(int eTime, int cancelOrdID) :
	Event(eTime)

{

	this->cancelledOrderID = cancelOrdID;

}



void CancelEvent::Execute(Restaurant * pRest)

{
	Order *Ord = pRest->GetNormalOrderById(cancelledOrderID);
	pRest->RemoveFromAllOrders(Ord);
	pRest->RemoveNormalOrderById(cancelledOrderID);
}





CancelEvent::~CancelEvent()

{

}