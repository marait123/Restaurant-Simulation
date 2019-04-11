#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
//#include "..\GUI\GUI.h"  //Already Included in LoadAction
#include "..\Generic_DS\Queue.h" 

#include "..\Events\Event.h"
#include "..\Events\PromoteEvent.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancelEvent.h"
#include "RegionManager.h"

//#include "..\LoadAction.h"
#include "..\SaveAction.h"
class LoadAction;
#include "..\GUI\GUI.h"
#include"../utility functions/strutils.h"

/// standard includes
#include<string>
#include <sstream>
#include <time.h>
#include"../Generic_DS/Vector.h"

//
// it is the maestro of the project
class Restaurant  
{	
private:

	RegionManager Region[4];
	LoadAction *Load;
	SaveAction *Save;
	string LoadedFile;
	GUI *pGUI;
	Event *pEvent;
	Motorcycle *pMotor;
	Order *pOrder;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file


	Vector<Order*> AllOrders;

	///<summary>represents the timestep after which the Normal orders are promoted</summary>
	int AutoPromoteTimeStep;

	///this is the current timestep of the program
	int CurrentTimeStep;

	/// ==> 

	//	DEMO-related members. Should be removed in phases 1&2

	Queue<Order*> DEMO_Queue;	//Important: This is just for demo

	/// ==>
	//

	// TODO: Add More Data Members As Needed

	//
public:
	
	Restaurant();

	~Restaurant();

	void AddEvent(Event* pE);	//adds a new event to the queue of events

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep

	void RunSimulation();

	//Functions to control Orders

	///HMANA6399 :: I Added those here to because Rest Class is the maestro and the controller

	///of Orders lists.

	//void AddtoDemoQueue(Order* po);	//adds an order to the demo queue

	void AddOrderToNormal(Order* newOrd);

	void AddOrderToFrozen(Order* newOrd);

	void AddOrderToVIP(Order* newOrd);

	

	//Some Specific functions for the Normal Order for Cancelation and Promotion


	///HMANA6399 :: Beta version, Requires a traverse-frindly DS

	///like a vector so that its el.s are easily accessed by []

	void RemoveNormalOrder(Order*);
	void RemoveNormalOrderById(int);
	Order* GetNormalOrderById(int);


	/// ==> 

	///  DEMO-related functions. Should be removed in phases 1&2

	//void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2

	Order* getDemoOrder();			//return the front order from demo queue

	/// ==> 
	///


	int GetPromotionLimit(int Max);

	void SetPromotionTimeStep(int);

	void LoadFromFile(string fileName);
	//
	// TODO: Add More Member Functions As Needed
	//
	void IncreaseCurrentTime();

	void InterActive();
	void ProcessInterActive();

    void StepByStep();
	void Silent();
	void AddToAllOrders(Order*);
	void RemoveFromAllOrders(Order* );
	Vector<Order*>& GetAllOrdersVec();

	void Phase1Delete();

};
 