#include "Motorcycle.h"

int Motorcycle::ID = -1;

Motorcycle::Motorcycle()
{
	ID++;
	this->status = IDLE;
}

void Motorcycle::SetSpeed(int S,MotorcycleType M)
{
	this->speed = S;
	this->Moto_Type = M;
}
int Motorcycle::GetSpeed()
{
	return this->speed;
}
void Motorcycle::SetRegion(REGION R)
{
	this->region = R;
}
REGION Motorcycle::GetRegion()
{
	return this->region;
}
void Motorcycle::SetOrder(ORD_TYPE O)
{
	this->type = O;
}
ORD_TYPE Motorcycle::GetOrder()
{
	return this->type;
}

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
