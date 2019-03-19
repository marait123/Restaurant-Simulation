#ifndef _REGION_MANAGER_
#define _REGION_MANAGER_


#include"Order.h"
#include"Motorcycle.h"

//class Restaurant;//Forward Declaration

class RegionManager
{
	// Restaurant *pRest;
     Order *ListOfOrders ;
     Motorcycle *ListOfMotorcycles ;
	 REGION RegionType;

   

	 int OrderCount;
	 int MotorsCount;

     public :

	 RegionManager();

   Order* getListOfOrders();
	 void setListOfOrders(Order *Orders);

	 Motorcycle* getListOfMotorcycles();
	 void setListOfMotorcycles(Motorcycle*cycles); 

	 int getRegionID() ;
	 void AddOrder(Order*order); 

	 void setRegionID(REGION RegionID);
	 void AddMotorCycle(Motorcycle motor) ;

	 Order GetOrderByID(int RegionID) ;

	 

	 void SetOrderCount(int OrderC);
	 void SetMotorsCount(int MotorC);
	 int GetOrderCount();
	 int GetMotorsCount();
	 ~RegionManager();
};
#endif 
	

