#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"

#include "../LoadAction.h"
Restaurant::Restaurant() 
{

	CurrentTimeStep = 0;
	AutoPromoteTimeStep = 0;
	
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		InterActive();
		break;
	case MODE_STEP:
		StepByStep();
		break;
	case MODE_SLNT:
		Silent();
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////

void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events

{

	EventsQueue.enqueue(pE);
	
}



//Executes ALL events that should take place at current timestep

void Restaurant::ExecuteEvents(int CurrentTimeStep)

{

	Event *pE;

	while( EventsQueue.peekFront(pE) )	//as long as there are more events

	{

		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time

			return;
		pE->Execute(this);

		EventsQueue.dequeue(pE);	//remove event from the queue

		delete pE;		//deallocate event object from memory

	}



}


Restaurant::~Restaurant()
{
		delete pGUI;
}

////////////////



//void restaurant::addtodemoqueue(order *pord)

//{

//	demo_queue.enqueue(pord);

//}



void Restaurant::AddOrderToVIP(Order *newOrd)

{

	/*// --> Execute Add fn of NormalOrders list 

	DEMO_Queue.enqueue(newOrd);

	///HMANA6399 :: I left this line for testing*/
	switch( newOrd->GetRegion() )
	{
	    case A_REG :	
			this->Region[0].AddOrderToVIP(newOrd);
			break;
		case B_REG :
			this->Region[1].AddOrderToVIP(newOrd);
			break;
		case C_REG :
			this->Region[2].AddOrderToVIP(newOrd);
			break;
		case D_REG :
			this->Region[3].AddOrderToVIP(newOrd);
			break;
	}
}



void Restaurant::AddOrderToNormal(Order *newOrd)

{

	// add to normal orders in the region class and so is the other AddOreder functions
	// --> Execute Add fn of FrozenOrders list 
	if (newOrd->GetRegion == REGION::A_REG) {
		//this->Region[0].
	}
	DEMO_Queue.enqueue(newOrd);

	///HMANA6399 :: I left this line for testing*/
	switch( newOrd->GetRegion() )
	{
	    case A_REG :	
			this->Region[0].AddOrderToNormal(newOrd);
			break;
		case B_REG :
			this->Region[1].AddOrderToNormal(newOrd);
			break;
		case C_REG :
			this->Region[2].AddOrderToNormal(newOrd);
			break;
		case D_REG :
			this->Region[3].AddOrderToNormal(newOrd);
			break;
	}
}



void Restaurant::AddOrderToFrozen(Order *newOrd)

{

	/*// --> Execute Add fn of VIPOrders list 

	DEMO_Queue.enqueue(newOrd);

	///HMANA6399 :: I left this line for testing*/
	switch(newOrd->GetRegion())
	{
	    case A_REG :	
			this->Region[0].AddOrderToFrozen(newOrd);
			break;
		case B_REG :
			this->Region[1].AddOrderToFrozen(newOrd);
			break;
		case C_REG :
			this->Region[2].AddOrderToFrozen(newOrd);
			break;
		case D_REG :
			this->Region[3].AddOrderToFrozen(newOrd);
			break;
	}
}





Order * Restaurant::GetNormalOrderById(int ID)

{

	//1 --> Traverse the orders list

	//2 --> return a pointer to the Order - if found -, either return nullptr

	return nullptr;

}

int Restaurant::GetPromotionLimit(int Max)
{
	return Max;
}



void Restaurant::RemoveNormalOrder(Order* remOrd)

{

	// --> Execute Remove fn. of NormalOrders list

	DEMO_Queue.dequeue(remOrd);

	///HMANA6399 :: I left this line for testing

}




Order* Restaurant::getDemoOrder()

{

	Order* pOrd;

	DEMO_Queue.dequeue(pOrd);

	return pOrd;



}



/// ==> end of DEMO-related function



////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

/*void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}*/



/// ==> end of DEMO-related function

void Restaurant::InterActive()
{
	int EventCnt;	
	Order* pOrd;
	Event* pEv;

	pGUI->PrintMessage("InterActive Mode , Mouse Click to Continue");
	pGUI->waitForClick();
	pGUI->PrintMessage("Please enter file to load , Mouse Click to Continue");
	pGUI->waitForClick();
	
	LoadedFile = pGUI->GetString();
	if (LoadedFile.find(".txt") == -1) LoadedFile += ".txt";
	
	Load = new LoadAction(LoadedFile,this);
	Load->Execute();	// first load the file 
	this->ProcessInterActive(); // second do the interactive stuff

	//pGUI->waitForClick();

	//Save->Execute(); // do the save stuff
}

void Restaurant::IncreaseCurrentTime()
{
	this->CurrentTimeStep ++;
}

void Restaurant::ProcessInterActive()
{
	while( !this->EventsQueue.isEmpty() )  // this is the event loop where every order gets assigned to a motor cycle
	{
		pGUI->PrintMessage("Mouse Click To increase TimeStep");
		pGUI->waitForClick();
		IncreaseCurrentTime();
		this->ExecuteEvents(CurrentTimeStep);
		//Excute Events;
	}
	//Save->Execute();
}


void Restaurant::StepByStep()
{
	int EventCnt;	
	Order* pOrd;
	Event* pEv;

	pGUI->PrintMessage("Step By Step Mode , Mouse Click to Continue");
	pGUI->waitForClick();

	pGUI->PrintMessage("Please enter file to load , Mouse Click to Continue");
	pGUI->waitForClick();
	
	LoadedFile = pGUI->GetString();
	if (LoadedFile.find(".txt") == -1) LoadedFile += ".txt";
	Load = new LoadAction(LoadedFile,this);
	Load->Execute();

	//Sleep(1000); // wait 1 second for the next function call
}

void Restaurant::Silent()
{
	int EventCnt;	
	Order* pOrd;
	Event* pEv;

	pGUI->PrintMessage("Silent Mode , Mouse Click to Continue");
	pGUI->waitForClick();

	pGUI->PrintMessage("Please enter file to load , Mouse Click to Continue");
	pGUI->waitForClick();
	
	LoadedFile = pGUI->GetString();
	if (LoadedFile.find(".txt") == -1) LoadedFile += ".txt";
	Load = new LoadAction(LoadedFile,this);
	Load->Execute();
}







void Restaurant::LoadFromFile(string fileName){
	ifstream LoadFile = ifstream(); //assigns and tries to open the file
	LoadFile.open( fileName.c_str() );
	if (LoadFile.is_open()) 
	{
		    string line;
		    int Froz , Nrm , Fst; 
			int Fst_Count , Nrm_Count , Froz_Count;
			LoadFile >> Froz >> Nrm >> Fst;

			RegionManager::SetFastMotorSpeed(Fst);
			RegionManager::SetNormalMotorSpeed(Nrm);
			RegionManager::SetFrozenMotorSpeed(Froz);
			
			for( int i = 0 ; i < 4 ; i++)
			{
				
				LoadFile >> Fst_Count >> Nrm_Count >> Froz_Count;
				
				this->Region[i].SetFastMotorCount(Fst_Count);
				this->Region[i].SetNormalMotorCount(Nrm_Count);
				this->Region[i].SetFrozenMotorCount(Froz_Count);
				int a;
			}
			
			/*5 3 1  ➔ no. of motorcycles in Region A 
			6 3 2  ➔ no. of motorcycles in Region B 
			4 2 1  ➔ no. of motorcycles in Region C 
			9 4 2  ➔ no. of motorcycles in Region D 
		*/
			int PromotionLimit; 
			LoadFile >> PromotionLimit;
			this->SetPromotionTimeStep(PromotionLimit);
			
			// Event Assignation
			int EventNumber; 
			LoadFile >> EventNumber; 

			char EventType;

			
			const int MaxENum  = 6; // Max Number of Line Elements 
			string lineElemets[MaxENum];

		    int  TS  , ID  ;
			float  DST , MON , ExMon;
			char  TYP , Reg ;
			/* Arrival event line have the following info R TS TYP ID DST MON  REG 
			  where R means an arrival event, TYP is the order type (N: normal, F: frozen, V: VIP). TS is the arrival time step. 
			  The ID is a unique sequence number that identifies each order. 
			  DST is the distance (in meters) between the order delivery location and the restaurant, 
			  MON is the total order money and REG is the order region.  
			 
			  Cancellation event line have the following info X TS ID 
			
			  where X means an order cancellation event occurring at time TS, and ID is the id of the order to be canceled. This ID must be of a Normal order. ❑ 
			  
			  Promotion event line have the following info P TS ID ExMon
			  
			  where P means an order promotion event occurring at time TS,and ID is the id of the order to be promoted to be VIP. This ID must be of a Normal order. 
			  ExMon if the extra money the customer paid for promotion*/
			 ORD_TYPE O_Type ;
			 REGION R_Type;

			 int counter = 0;
			while( !(LoadFile.eof()) && counter < EventNumber )
			{
				/*cin>>EventType;*/
				

				LoadFile>>EventType;

				switch (EventType)
				{
				case 'R':{
					
					        LoadFile  >> TS >> TYP >> ID >> DST >> MON >> Reg;
						 

						    TYP =  toupper(TYP);
                            switch(TYP)
						    {
							case 'N' :
								O_Type = TYPE_NRM ;
								break;
							case 'F' :
								O_Type = TYPE_FROZ ;
								break;
							case 'V' :
								O_Type = TYPE_VIP;
								break;
						    }
	
	
	
							switch(Reg)
						    {
							case 'A' :
								R_Type = A_REG;
								break;
							case 'B' :
								R_Type = B_REG;
								break;
							case 'C' :
								R_Type = C_REG;
								break;
							case 'D' :
								R_Type = D_REG;
								break;
						    }


						 Event *pEvent = new ArrivalEvent(TS,ID,O_Type,R_Type);
						 this->EventsQueue.enqueue(pEvent);
						 break;
						 }
						   
			   case 'X':{
				        LoadFile >> TS >> ID ;
						Event *pEvent = new CancelEvent( TS , ID ); 
						this->EventsQueue.enqueue(pEvent);
						break;
						}

			   case 'P':{
				        LoadFile >> TS >> ID >> ExMon;
						Event *pEvent = new PromoteEvent(TS,ID,ExMon);
						this->EventsQueue.enqueue(pEvent);
						break;
						}
			      default :
						    break;
				}
				counter++;
			}
			/*
			8       ➔ no. of events in this file 
			R 7 N 1 15 110 A  ➔ Arrival event 
			R 9 N 2 7 56 B 
			R 9 V 3 21 300 B 
			R 12 F 4 53 42 C 
			X 15 1     ➔ Cancellation event 
			R 19 N 5 17 95 D 
			P 19 2 62    ➔ promotion event 
			R 25 F 6 33 127 D */
			
		}
}
	



void Restaurant::SetPromotionTimeStep(int P_TimeSkip)
{
	this->AutoPromoteTimeStep = P_TimeSkip;
}
