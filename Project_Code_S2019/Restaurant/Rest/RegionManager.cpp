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
	FastMotorCount = FTMC;
}

void RegionManager::SetNormalMotorCount(int NMC)
{
	NormalMotorCount = NMC;
}

int RegionManager::GetFrozenMotorCount()
{
	return this->FrozenMotorCount;
}

int RegionManager::GetFastMotorCount()
{
	return this->FastMotorCount;
}

int RegionManager::GetNormalMotorCount()
{
	return this->NormalMotorCount;
}

void RegionManager::AddToFrozenOrders(Order *od)
{
	this->FrozenOrder.enqueue(od);
}

void RegionManager::AddToNormalOrders(Order *od)
{
	BDPair<int, Order*> MP;
	MP.SetKey(od->GetID());
	MP.SetData(od);
	this->NormalOrders.Insert(MP);
}

int RegionManager::GetNumberOfWaitingOrders()
{
	return this->NormalOrders.GetCount() + this->VipOrders.GetCount()+this->FrozenOrder.GetCount();
}


void RegionManager::AddToVIPOrders(Order * od)
{
	/// money distacne and time
	double priority = (od->GetMoney() / (od->getArrTime()*od->GetDistance()));
	
	this->VipOrders.enqueue(Pair<double, Order*>(priority, od));
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

bool RegionManager::CancelNormalOrder(int ID){
	try{
	bool isThere = this->NormalOrders.Contains(ID); 
	if(isThere == true)
	this->NormalOrders.Remove(ID);

	return isThere;
	}
	catch(exception& ex){
		return false;
	}

}

Order* RegionManager::GetNormalOrder(int ID){
	try{
	if(this->NormalOrders.Contains(ID))
	return this->NormalOrders.At(ID);
	else
	{
		return NULL;
	}
	}
	catch(exception& ex){
		return NULL;
	}
}

RegionManager::~RegionManager()
{
	delete this->ListOfMotorcycles;
	//delete this->ListOfOrders;
}

void RegionManager::Phase1Delete()
{
/*
	Map<int, Order*> NormalOrders;
	Queue<Order*> FrozenOrder;
	priority_q<Pair<double, Order*>> VipOrders;
*/
	Order* ord;
	Pair<double, Order*> tempPair;
	VipOrders.dequeue(tempPair);
	FrozenOrder.dequeue(ord);
	this->NormalOrders.Deque();  // i have done the 
	// for the normal order since  it is stored on the tree it is you will have to get it in the most effecient way // i onley have access to the orders through ids only
	
}
