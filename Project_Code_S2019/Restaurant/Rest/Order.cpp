#include "Order.h"
Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int eTime, double ordMon  , double ordDist)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	this->totalMoney = ordMon ;
	this->ArrTime = eTime;
	this->Distance = ordDist;
	this->WaitingTime = 0;
	this->FinishTime = 0;
	this->ServTime = 0;
}


Order::~Order()
{}


int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::SetType(ORD_TYPE T)
{
	this->type= T;
}


REGION Order::GetRegion() const
{
	return Region;
}


void Order::SetDistance(int d)
{
	Distance = d>0 ? d : 0;
}


int Order::GetDistance() const
{
	return Distance;
}


//TIMES
void Order::updateFinishTime()
{
	FinishTime = ArrTime + ServTime + WaitingTime;
}


void Order::setWaitingTime(int t)
{
	this->WaitingTime = t;
	updateFinishTime();
}


void Order::setServTime(int t)
{
	this->ServTime = t;
	updateFinishTime();
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

int Order::getWaitingTime() 
{
	return this->WaitingTime;
}

bool Order::operator>(const Order& od) const
{
	return	this->FinishTime < od.FinishTime ||
			(this->FinishTime == od.FinishTime && this->ServTime < od.ServTime); 
}


bool Order::operator<(const Order & od) const
{
	return	this->FinishTime > od.FinishTime ||
			(this->FinishTime == od.FinishTime && this->ServTime > od.ServTime); 
}


bool Order::operator==(const Order & od) const
{
	return	this->FinishTime == od.FinishTime ||
			this->ServTime == od.ServTime;
}


void Order::IncreaseMoney(double ammount)
{
	this->totalMoney += ammount;
}


double Order::GetMoney()
{
	return this->totalMoney;
}
