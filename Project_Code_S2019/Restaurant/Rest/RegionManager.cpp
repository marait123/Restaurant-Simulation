#include "RegionManager.h"
#include"Restaurant.h"


RegionManager::RegionManager()
{
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 2; ++j)
			MotorCyclesCounts[i][j] = 0;
	AllMotorsCount = 0;
	OrderCount = 0;
	TotalServTime = 0;
	TotalWaitingTime = 0;
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


bool RegionManager::PopMotorCycle(Motorcycle*& MC, MotorcycleType typ, STATUS stat)
{
	if (ListOfMotorcycles[typ][stat].getSize() == 0) return false;
	MC = ListOfMotorcycles[typ][stat][0];
	RemoveMotorCycle(MC, 0);
	//TODO :: Check that this will not delete the whole object
	return true;
}


////////////////////////////////////////////////////////////////////////
//Functions for Phase2
////////////////////////////////////////////////////////////////////////
//TODO :: Ph2 : Every Timestep, check for the arrived MCs, remove them from the SERV list to the IDLE list
void RegionManager::CheckArrivedMotorCycles()
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < ListOfMotorcycles[(MotorcycleType)i][SERV].getSize(); ++j) {
			if (!ListOfMotorcycles[(MotorcycleType)i][SERV][i]->DecrementDeliveryTime()) {
				Motorcycle* MC_Back = ListOfMotorcycles[(MotorcycleType)i][SERV][i];
				RemoveMotorCycle(ListOfMotorcycles[(MotorcycleType)i][SERV][i], i);
				MC_Back->SetStatus(IDLE);
				AddMotorCycle(MC_Back);
			}
		}
	}
}


Motorcycle* RegionManager::GetIdleMC(ORD_TYPE ord_typ)
{
	Motorcycle* MC = nullptr;
	///Check there's a suitable MC in order according to the order type and get it
	switch (ord_typ)
	{
	case TYPE_NRM:
		if (PopMotorCycle(MC, Normal, IDLE)) break;
		else PopMotorCycle(MC, Fast, IDLE);
		break;
	case TYPE_FROZ:
		PopMotorCycle(MC, Frozen, IDLE);
		break;
	case TYPE_VIP:
		if (PopMotorCycle(MC, Fast, IDLE)) break;
		else if (PopMotorCycle(MC, Normal, IDLE)) break;
		else PopMotorCycle(MC, Frozen, IDLE);
	default:
		break;
	}

	return MC;
}


bool RegionManager::ServeOrder(Order* pOrd, int curTS)
{
	//Check for a Motorcycle, if not return false
	Motorcycle* MC = GetIdleMC(pOrd->GetType());
	if (MC == nullptr) return false;
	MC->SetStatus(SERV);
	AddMotorCycle(MC);	

	///Calculate WT of pOrd (currentTS - AT), add to TotalWaitingTime
	int WT = curTS - pOrd->getArrTime();
	pOrd->setWaitingTime(WT);
	TotalWaitingTime += WT;

	///Calculate ST of pOrd (OrdDist/v)
	int ST = ceil(pOrd->GetDistance()/MC->GetSpeed());
	pOrd->setServTime(ST);
	TotalServTime += ST;

	///Calculate the DeliveryTime of the MC ST*2
	MC->SetTimeUntillDelivery(2*ST);

	//HMANA6399 :: For better time effeciency, I suggest deleting the Order from its list after
	//				Serving it in the simulation loop. So no need to delete it here.
	//				Also I see better to call the function of adding it to the final priority_q
	//				For saving in the loop as well.
	//				Make sure that the deletion does not envolve Deleting the main object.
	//				Just moving the its pointer from its list to the PQ!!!
	//TODO :: Also we have to  see what to do regarding the Delete of the GUI
	return true;
}


void RegionManager::ServeAvailableOrders(Restaurant* pRest)
{
	int curTS = pRest->GetCurrentTimeStep();
	//First, VIP Orders
	while (!VipOrders.isEmpty()) {
		Pair<double, Order*> t_pair;
		VipOrders.peekFront(t_pair);
		if (!ServeOrder(t_pair.getSecond())) break;
	}

}

//////////////////////////////////////////////////
//Getters for Statistics in Save File
//////////////////////////////////////////////////
int RegionManager::GetMCCount() const
{
	return this->AllMotorsCount;
}


int RegionManager::GetOrderCount() const
{
	return this->OrderCount;
}


int RegionManager::GetTotalServTime() const
{
	return this->TotalServTime;
}


int RegionManager::GetTotalWaitingTime() const
{
	return this->TotalWaitingTime;
}


void RegionManager::SetOrderCount(int OrderC)
{
	this->OrderCount = OrderC;
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

//TODO :: See what to do for this
//void RegionManager::Phase1Delete(Order**& ordList)
//{
//	ordList = new Order*[3]; // this array will hold the pointers to the orders deleted to use it to delete from the gui
//
//	Pair<double, Order*> tempPair1;
//	bool yes = VipOrders.dequeue(tempPair1);
//	if (yes)
//		ordList[0] = tempPair1.getSecond();
//	else 
//		ordList[0] = NULL;
//
//	yes = FrozenOrder.dequeue(ordList[1]);
//	
//	if (!yes)
//		ordList[1] = NULL;
//
//	BDPair<int, Order*> tempPair2;
//	yes = this->NormalOrders.peak(tempPair2);
//	if (yes == true) {
//		ordList[2] = tempPair2.GetData();
//		this->NormalOrders.Deque();
//	}
//	else
//	{
//		ordList[2] = NULL;
//	}
//
//	// i have done the 
//	// for the normal order since  it is stored on the tree it is you will have to get it in the most effecient way // i onley have access to the orders through ids only
//	
//}
