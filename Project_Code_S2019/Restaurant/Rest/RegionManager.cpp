#include "RegionManager.h"


int RegionManager::FrozenMotorSpeed = 0;
int RegionManager::FastMotorSpeed = 0;
int RegionManager::NormalMotorSpeed = 0;

RegionManager::RegionManager()
{
}

//Order* RegionManager::getListOfOrders()
//{
//	return this->ListOfOrders;
//}
//
//void RegionManager::setListOfOrders(Order *Orders)
//{
//	this->ListOfOrders = Orders;
//}

Motorcycle* RegionManager::getListOfMotorcycles()
{
	return this->ListOfMotorcycles;
}
void RegionManager::setListOfMotorcycles(Motorcycle*cycles)
{
}
int RegionManager::getRegionID()
{
	return this->RegionType;
}
void RegionManager::AddOrder(Order*order)
{

}

void RegionManager::setRegionID(REGION RegionID)
{
	this->RegionType = RegionID;
}
void RegionManager::AddMotorCycle(Motorcycle motor) 
{
}
void RegionManager::SetFrozenMotorSpeed(float FMS)
{
	FrozenMotorSpeed = FMS;
}
void RegionManager::SetFastMotorSpeed(float FMS)
{
	FastMotorSpeed = FMS;
}
void RegionManager::SetNormalMotorSpeed(float NMS)
{
	RegionManager::NormalMotorSpeed = NMS;
}
void RegionManager::SetOrderCount(int OrderC)
{
	this->OrderCount = OrderC;
}
 
int RegionManager::GetOrderCount()
{
	return this->OrderCount;
}
void RegionManager::SetFrozenMotorCount(int FZMC)
{
	this->FrozenMotorCount = FZMC;
}

void RegionManager::SetFastMotorCount(int FTMC)
{
	this->FastMotorCount = FTMC;
}

void RegionManager::SetNormalMotorCount(int NMC)
{
	NormalMotorCount = NMC;
}


//
//Order RegionManager::GetOrderByID(int RegionID)
//{
//	for(int i = 0 ; i < this->OrderCount ; i++)
//	{
//		if( ListOfOrders[i].GetRegion() == RegionID)
//			return  this->ListOfOrders[i];
//	}
//}
RegionManager::~RegionManager()
{
	delete this->ListOfMotorcycles;
	//delete this->ListOfOrders;
}