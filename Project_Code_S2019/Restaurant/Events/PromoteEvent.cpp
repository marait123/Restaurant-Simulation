#include "PromoteEvent.h"

#include"../Rest/Restaurant.h"





PromoteEvent::PromoteEvent(int eTime, int promOrdId, double exMon) :

	Event(eTime)

{

	this->promotededOrderID = promOrdId;

	this->extraMoney = exMon;

}

void PromoteEvent::MaxLimit(int Max)

{
	this->PromotionLimit = Max;
}

void PromoteEvent::Execute(Restaurant * pRest)

{

	Order* promOrd = pRest->GetNormalOrderById(this->promotededOrderID);

	if (promOrd != nullptr) {

		promOrd->IncreaseMoney(this->extraMoney);

		promOrd->SetType(TYPE_VIP);

		pRest->RemoveNormalOrder(promOrd);

		pRest->AddOrderToVIP(promOrd);

	}
	
}





PromoteEvent::~PromoteEvent()

{

}