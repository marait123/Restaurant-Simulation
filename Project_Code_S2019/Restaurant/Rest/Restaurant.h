#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"


#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	
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
	Order* GetNormalOrderById(int ID);
	///HMANA6399 :: Beta version, Requires a traverse-frindly DS
	///like a vector so that its el.s are easily accessed by []
	void RemoveNormalOrder(Order*);
	
	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 


	//
	// TODO: Add More Member Functions As Needed
	//

};

#endif