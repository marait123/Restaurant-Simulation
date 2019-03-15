#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	isDelivered = true;
	
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
