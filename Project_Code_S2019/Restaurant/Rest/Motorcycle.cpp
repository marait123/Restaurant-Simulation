#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
	this->status = IDLE;
	this->DeliveryTime = 0;
}

Motorcycle::Motorcycle(int sp, REGION reg, MotorcycleType mc_type)
	: speed(sp), region(reg), Moto_Type(mc_type)
{
	status = IDLE;
	DeliveryTime = 0;
}

//TODO :: Remove if not needed
void Motorcycle::SetSpeed(int S,MotorcycleType M)
{
	this->speed = S;
	this->Moto_Type = M;
}


int Motorcycle::GetSpeed()
{
	return this->speed;
}

//TODO :: Remove if not needed
void Motorcycle::SetRegion(REGION R)
{
	this->region = R;
}


REGION Motorcycle::GetRegion()
{
	return this->region;
}


MotorcycleType Motorcycle::GetType()
{
	return this->Moto_Type;
}


///////////////////////////////////////////////////////
///Functions for Delivery Time
///////////////////////////////////////////////////////

int Motorcycle::GetTimeUntillDelivery()
{
	return this->DeliveryTime;
}


void Motorcycle::SetTimeUntillDelivery(int td)
{
	this->DeliveryTime = td;
}


bool Motorcycle::DecrementDeliveryTime()
{
	this->DeliveryTime--;
	return DeliveryTime >= 0;
}
////////////////////////////////////////////////////////


void Motorcycle::SetStatus(STATUS ST)
{
	this->status = ST;
}


STATUS Motorcycle::GetStatus()
{
	return this->status;
}


Motorcycle::~Motorcycle()
{
}
