#include "Order.h"


	//Order* pOrd = new Order(OrderID,OrdType,OrdRegion,this->EventTime, this->OrdMoney, this->OrdDistance);
//
Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int eTime, double ordMon  , double ordDist)
{

	ID = (id>0&&id<1000)?id:0;	//1<ID<999

	type = r_Type;

	Region = r_region;	

	isDelivered = true;

	this->totalMoney = ordMon ;
	this->ArrTime = eTime;
	this->Distance = ordDist;
	

}





Order::~Order()

{



}



int Order::GetID()

{

	return ID;

}


int Order::GetType() const

{

	return type;

}

void Order::SetType(ORD_TYPE T){

	this->type= T;
}



REGION Order::GetRegion() const

{

	return Region;

}



void Order::SetDistance(int d)

{

	Distance = d>0?d:0;

}



int Order::GetDistance() const

{

	return Distance;

}



int Order::getArrTime()

{

	return this->ArrTime;

}

int Order::getServTime()

{

	return this->ServTime;

}



int Order::getFinishTime()

{

	return this->FinishTime;

}





///<summary>this function promotes the order only if it is of the normal type</summary>

bool Order::Promote()

{

	if (this->type == ORD_TYPE::TYPE_NRM) {

		this->type = ORD_TYPE::TYPE_VIP;

		return true;

	}

	else

	{		

		return false;

	}



}
/// Marait:: this function return the priority index of the order to compare with other orders and be able to determine which on should precede the other 
float Order::GetPriorityIndex() const
{
	float pIndex = this->totalMoney * ArrTime / Distance;
	return pIndex;
}

bool Order::operator>(const Order& od) const
{
	return this->GetPriorityIndex() > od.GetPriorityIndex();
}

bool Order::operator<(const Order & od) const
{
	return this->GetPriorityIndex() < od.GetPriorityIndex();
}

bool Order::operator==(const Order & od) const
{
	return this->GetPriorityIndex() == od.GetPriorityIndex();
}

void Order::IncreaseMoney(double ammount)
{
	this->totalMoney += ammount;
}

double Order::GetMoney()
{
	return this->totalMoney;
}
