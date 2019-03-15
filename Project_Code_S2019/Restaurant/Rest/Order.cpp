#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
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

int Order::GetArrivalTime() const
{
	return this->ArrTime;
}

void Order::IncreaseMoney(double ammount)
{
	this->totalMoney += ammount;
}

void Order::SetType(ORD_TYPE newType)
{
	this->type = newType;
}
