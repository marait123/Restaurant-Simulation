#ifndef _REGION_MANAGER_
#define _REGION_MANAGER_


#include"Order.h"
#include"Motorcycle.h"

//class Restaurant;//Forward Declaration

class RegionManager
{
private:
	// Restaurant *pRest;
     Order *ListOfInActiceOrders ;
     Order *ListOfActiveOrders ;
     Motorcycle *ListOfMotorcycles ;
	 REGION RegionType;


   

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

 // not implemented yet // it is waiting for the suitable adt to store the frozen orders
	 void AddToFrozenOrders(Order*);

 // not implemented yet
	 void AddToNormalOrders(Order*);



// not implemented yet
	 void AddToVIPOrders(Order*);

	 ~RegionManager();




};
#endif 
	

	