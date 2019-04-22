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
	Order *pOrder;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	///Stores the speed of the three types of Motorcycles referenced to by the index
	int MotorcycleSpeeds[3];

	///<summary>represents the timestep after which the Normal orders are promoted</summary>
	int AutoPromoteTimeStep;

	///this is the current timestep of the program
	int CurrentTimeStep;

	bool isLoaded; //To repeat the program if the input file is not loaded

	// TODO: Add More Data Members As Needed

	//
public:
	
	Restaurant();

	~Restaurant();

	void AddEvent(Event* pE);	//adds a new event to the queue of events

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep

	void RunSimulation();

	//Functions related to Motorcycles
	void CheckArrivedMotorCycles();
	bool AssignMotorcycle(Order*); //TO BE COMPLETED IN PHASE isA
	//Functions to control Orders

	///HMANA6399 :: I Added those here to because Rest Class is the maestro and the controller

	///of Orders lists.

	void AddOrderToNormal(Order* newOrd);

	void AddOrderToFrozen(Order* newOrd);

	void AddOrderToVIP(Order* newOrd);

	

	//Some Specific functions for the Normal Order for Cancelation and Promotion
	void RemoveNormalOrder(Order*);
	void RemoveNormalOrderById(int);
	Order* GetNormalOrderById(int);

	Order* getDemoOrder();			//return the front order from demo queue

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

	void Phase1Delete();

};
 