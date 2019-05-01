#ifndef _REGION_MANAGER_
#define _REGION_MANAGER_
//#include"../Generic_DS/"

#include<cmath> //Because we use ceil

#include"../Generic_DS/BSDLL.h"
#include"Order.h"
#include"Motorcycle.h"
#include"../Generic_DS/Queue.h"
#include"../Generic_DS/Pair.h"
#include"../Generic_DS/priority_q.h"
#include"../Generic_DS/Vector.h"

class Restaurant;

class RegionManager
{
private:
	
	//Lists of Motorcycles, 2d Array of Vectors, First Index is for Type, second is for Status
	//Generally -> ListOfMotorcycles[MotrcycleType][STATUS]
	//Restaurant* pRest;
	Vector<Motorcycle*> ListOfMotorcycles[3][2];
	
	 //Counts for Motorcycles, 2D array, first Index is for Type, second is for STATUS
	 //Generally -> MotorCyclesCounts[MotorcycleType][STATUS]
	int MotorCyclesCounts[3][2];
	int AllMotorsCount;

	//For Statistics
	int TotalServTime;
	int TotalWaitingTime;
	int OrderCount;

	 // the lists of waiting orders
	 /*justification for the BSDLL:
	   1. it offers an O(logn) complexity of promotion
	   2. it offers an O(logn) complexity of cancelation
	   3. it offers an O(logn) retreival and insertion
	   4. it offers an O(logn) deletion*/
	 BSDLL<int, Order*> NormalOrders;
	 Queue<Order*> FrozenOrder;
	 priority_q<Pair<double, Order*>> VipOrders;

public :
	
	 RegionManager();
	
	//Setters and Getters for counters of Motorcycles
	void SetNormalMotorCount(int);
	void SetFastMotorCount(int);
	void SetFrozenMotorCount(int);

	//Functions for Motorcyles list
	bool AddMotorCycle(Motorcycle* mc);
	void RemoveMotorCycle(Motorcycle* mc, int id);
	bool PopMotorCycle(Motorcycle*& MC, MotorcycleType typ, STATUS stat);

	//Functions for Phase2
	void CheckArrivedMotorCycles();
	Motorcycle* GetIdleMC(ORD_TYPE ord_typ);
	bool ServeOrder(Order* pOrd, int curTS);
	bool ServeAvailableOrders(Restaurant* pRest);

	//For Statistics
	int GetMCCount() const;
	int GetOrderCount() const;
	int GetTotalServTime() const;
	int GetTotalWaitingTime() const;

	//void AddOrder(Order*order); 
	void SetOrderCount(int OrderC);

	
	 int GetFrozenMotorCount();
	 int GetFastMotorCount();
	 int GetNormalMotorCount();

	 void AddToFrozenOrders(Order*);

	 void AddToNormalOrders(Order*);

	// bool RemoveOrder(Order*);

	 int GetNumberOfWaitingOrders();

	 void AddToVIPOrders(Order*);
	 
	 bool CancelNormalOrder(int);
	 Order* GetNormalOrder(int);
	 bool DidFinish();


	 ~RegionManager();
};
#endif 
	

	