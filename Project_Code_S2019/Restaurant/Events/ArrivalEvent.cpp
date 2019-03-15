#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2
	Order* pOrd = new Order(OrderID,OrdType,OrdRegion);
	
	switch (OrdType) {
	case TYPE_NRM: 
		pRest->AddOrderToNormal(pOrd);
		break;

	case TYPE_FROZ:
		pRest->AddOrderToFrozen(pOrd);
		break;

	case TYPE_VIP:
		pRest->AddOrderToVIP(pOrd);
		break;

	default:
		break;
	}

	//pRest->AddtoDemoQueue(pOrd);
}