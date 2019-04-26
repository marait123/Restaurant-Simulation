#include "RegionManager.h"

RegionManager::RegionManager()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 2; ++j)
			MotorCyclesCounts[i][j] = 0;
	AllMotorsCount = 0;
	OrderCount = 0;
}

//////////////////////////////////////////////////////////////////////
// Functions for Motorcycles List
//////////////////////////////////////////////////////////////////////

bool RegionManager::AddMotorCycle(Motorcycle* mc)
{
	if (!mc) return false;
	ListOfMotorcycles[mc->GetType()][mc->GetStatus()].insert(mc);
	MotorCyclesCounts[mc->GetType()][mc->GetStatus()]++;
	AllMotorsCount += mc->GetStatus() == IDLE ? 1 : 0;
}


void RegionManager::RemoveMotorCycle(Motorcycle* mc, int id)
{
	if (mc == nullptr) return;
	MotorCyclesCounts[mc->GetType()][mc->GetStatus()]--;
	AllMotorsCount -= (mc->GetType() == IDLE);
	ListOfMotorcycles[mc->GetType()][mc->GetStatus()].RemoveByIndex(id);
}

//TODO :: Ph2 : Every Timestep, check for the arrived MCs, remove them from the SERV list to the IDLE list
void RegionManager::CheckArrivedMotorCycles()
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < ListOfMotorcycles[(MotorcycleType)i][SERV].getSize(); ++j) {
			if (!ListOfMotorcycles[(MotorcycleType)i][SERV][i]->DecrementDeliveryTime()) {
				Motorcycle* MC_Back = new Motorcycle(*ListOfMotorcycles[(MotorcycleType)i][SERV][i]);
				AddMotorCycle(MC_Back);
				RemoveMotorCycle(ListOfMotorcycles[(MotorcycleType)i][SERV][i], i);
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////

void RegionManager::AddOrder(Order*order)
{
}


void RegionManager::SetOrderCount(int OrderC)
{
	this->OrderCount = OrderC;
}
 

int RegionManager::GetOrderCount()
{
	return this->OrderCount;
}

//TODO :: Remove if not needed
void RegionManager::SetFrozenMotorCount(int FZMC)
{
	this->MotorCyclesCounts[Frozen][IDLE] = FZMC;
}

//TODO :: Remove if not needed
void RegionManager::SetFastMotorCount(int FTMC)
{
	this->MotorCyclesCounts[Fast][IDLE] = FTMC;
}

//TODO :: Remove if not needed
void RegionManager::SetNormalMotorCount(int NMC)
{
	this->MotorCyclesCounts[Normal][IDLE] = NMC;
}

//TODO :: Remove if not needed
int RegionManager::GetFrozenMotorCount()
{
	return this->MotorCyclesCounts[Frozen][IDLE];
}


int RegionManager::GetFastMotorCount()
{
	return this->MotorCyclesCounts[Fast][IDLE];
}


int RegionManager::GetNormalMotorCount()
{
	return this->MotorCyclesCounts[Normal][IDLE];
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
	/// money, distance and time
	double priority = (od->GetMoney() / (od->getArrTime()*od->GetDistance()));
	
	this->VipOrders.enqueue(Pair<double, Order*>(priority, od));
}


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
	//TODO :: Make sure that there are not any pointer-defined data member to be deleted
}

void RegionManager::Phase1Delete(Order**& ordList)
{
/*
	Map<int, Order*> NormalOrders;
	Queue<Order*> FrozenOrder;
	priority_q<Pair<double, Order*>> VipOrders;
*/
	ordList = new Order*[3]; // this array will hold the pointers to the orders deleted to use it to delete from the gui

	Pair<double, Order*> tempPair1;
	bool yes = VipOrders.dequeue(tempPair1);
	if(yes == true)
	ordList[0] = tempPair1.getSecond();
	else
	{
		ordList[0] = NULL;
	}

	yes = FrozenOrder.dequeue(ordList[1]);
	if (yes == false) {
		ordList[1] = NULL;
	}

	BDPair<int, Order*> tempPair2;
	yes = this->NormalOrders.peak(tempPair2);
	if (yes == true) {
		ordList[2] = tempPair2.GetData();
		this->NormalOrders.Deque();
	}
	else
	{
		ordList[2] = NULL;
	}

	// i have done the 
	// for the normal order since  it is stored on the tree it is you will have to get it in the most effecient way // i onley have access to the orders through ids only
	
}

bool RegionManager::DidFinish()
{
	// no orders are waiting to be assigned to motorcycles
	bool finish = this->NormalOrders.IsEmpty() && this->VipOrders.isEmpty() && this->FrozenOrder.isEmpty();
	
	/*no motorcycles are serving*/
	finish = finish && this->ListOfMotorcycles[MotorcycleType::Normal][STATUS::SERV].isEmpty();
	finish = finish && this->ListOfMotorcycles[MotorcycleType::Frozen][STATUS::SERV].isEmpty();
	finish = finish && this->ListOfMotorcycles[MotorcycleType::Fast][STATUS::SERV].isEmpty();
	
	return finish;
}
