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
	// Restaurant *pRest;
  //
	/*
	 Vector<Order*> DeliveredOrdersList;  // it is filled with the order after its finish time has been determined
	 Vector<Order*> UnderServiceOrdersList;  // it is filled once the order is assigned to a motorcycle
	 */

     Motorcycle *ListOfMotorcycles ;
	 REGION RegionType;


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

	 int AllMotorsCount;

	 int FrozenMotorCount;
	 int FastMotorCount;
	 int NormalMotorCount;
	 
	 static int FrozenMotorSpeed;
	 static int FastMotorSpeed;
	 static int NormalMotorSpeed;

     public :
	
	 RegionManager();

   /*  Order* getListOfOrders();
	 void setListOfOrders(Order *Orders);*/

	 Motorcycle* getListOfMotorcycles();
	 void setListOfMotorcycles(Motorcycle*cycles); 

	 int getRegionID() ;
	 void AddOrder(Order*order); 

	 void setRegionID(REGION RegionID);
	 void AddMotorCycle(Motorcycle motor) ;

	// Order GetOrderByID(int RegionID) ;


	 static void SetFrozenMotorSpeed(float);
	 static void SetFastMotorSpeed(float);
	 static void SetNormalMotorSpeed(float);

	 void SetOrderCount(int OrderC);
	 //void SetMotorsCount(int MotorC);
	 int GetOrderCount();
	 //int GetMotorsCount();
	 void SetFrozenMotorCount(int);
	 void SetFastMotorCount(int);
	 void SetNormalMotorCount(int);

	 int GetFrozenMotorCount();
	 int GetFastMotorCount();
	 int GetNormalMotorCount();

	 void AddToFrozenOrders(Order*);

	 void AddToNormalOrders(Order*);

	 int GetNumberOfWaitingOrders();

	 void AddToVIPOrders(Order*);
	 
	 bool CancelNormalOrder(int);
	 Order* GetNormalOrder(int);



	 ~RegionManager();

	 void Phase1Delete();


};
#endif 
	

	