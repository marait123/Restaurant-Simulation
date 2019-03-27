#include "CancelEvent.h"

#include"../Rest//Restaurant.h"





CancelEvent::CancelEvent(int eTime, int cancelOrdID) :
	Event(eTime)

{

	this->cancelledOrderID = cancelOrdID;

}



void CancelEvent::Execute(Restaurant * pRest)

{

	Order* pCancOrd = pRest->GetNormalOrderById(this->cancelledOrderID);

	if (pCancOrd) {

		pRest->RemoveNormalOrder(pCancOrd);

	}

	else {

		// TODO :: Handle this!

	}

	///HMANA :: DANGER! Should be revised

	delete pCancOrd;

}





CancelEvent::~CancelEvent()

{

}