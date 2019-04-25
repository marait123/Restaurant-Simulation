#ifndef _REGION_MANAGER_
#define _REGION_MANAGER_
//#include"../Generic_DS/"

#include"../Generic_DS/BSDLL.h"
#include"Order.h"
#include"Motorcycle.h"
#include"../Generic_DS/Queue.h"
#include"../Generic_DS/Pair.h"
#include"../Generic_DS/priority_q.h"
#include"../Generic_DS/Vector.h"

//class Restaurant;//Forward Declaration

class RegionManager
{
private:
	
	//Lists of Motorcycles, 2d Array of Vectors, First Index is for Type, second is for Status
	//Generally -> ListOfMotorcycles[MotrcycleType][STATUS]
	Vector<Motorcycle*> ListOfMotorcycles[3][2];
	
	 //Counts for Motorcycles, 2D array, first Index is for Type, second is for STATUS
	 //Generally -> MotorCyclesCounts[MotorcycleType][STATUS]
	int MotorCyclesCounts[3][2];
	int AllMotorsCount;

	 // the lists of waiting orders
	 /*justification for the BSDLL:
	   1. it offers an O(logn) complexity of promotion
	   2. it offers an O(logn) complexity of cancelation
	   3. it offers an O(logn) retreival and insertion
	   4. it offers an O(logn) deletion*/
	 BSDLL<int, Order*> NormalOrders;
	 Queue<Order*> FrozenOrder;
	 priority_q<Pair<double, Order*>> VipOrders;



	 int OrderCount;


public :
	
	 RegionManager();
	
	//Setters and Getters for counters of Motorcycles
	void SetNormalMotorCount(int);
	void SetFastMotorCount(int);
	void SetFrozenMotorCount(int);

	//Functions for Motorcyles list
	bool AssignOrderToMotorcycle(Order* pOrd);
	bool AddMotorCycle(Motorcycle* mc);
	void RemoveMotorCycle(Motorcycle* mc, int id);
	void CheckArrivedMotorCycles();


	void AddOrder(Order*order); 
	void SetOrderCount(int OrderC);
	int GetOrderCount();

	
	 int GetFrozenMotorCount();
	 int GetFastMotorCount();
	 int GetNormalMotorCount();

	 void AddToFrozenOrders(Order*);

	 void AddToNormalOrders(Order*);

	 int GetNumberOfWaitingOrders();

	 void AddToVIPOrders(Order*);
	 
	 bool CancelNormalOrder(int);
	 Order* GetNormalOrder(int);

	 void Phase1Delete(Order**& );

	 ~RegionManager();
};
#endif 
	

	