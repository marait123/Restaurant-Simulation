﻿#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"

#include "../LoadAction.h"
#include"RegionManager.h"

Restaurant::Restaurant() 
{

	CurrentTimeStep = 0;
	AutoPromoteTimeStep = 0;
	
	pGUI = NULL;
	isLoaded = true;
}


Restaurant::~Restaurant()
{
		delete pGUI;
}

RegionManager& Restaurant::GetRegion(REGION R)
{
	switch(R)
	{
	    case A_REG:
			return Region[0];
		case B_REG:
			return Region[1];
		case C_REG:
			return Region[2];
		case D_REG:
			return Region[3];
	}
}
void Restaurant::RunSimulation()
{
	pGUI = new GUI(this);
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
	default:
		InterActive();
		break;
	};
}

////////////////////////////////////////////////
//Functions related to Motorcycles
////////////////////////////////////////////////

//At each timestep, check the arrived MCs for all the regions
void Restaurant::CheckArrivedMotorCycles()
{
	for (int r = 0; r < 4; ++r) {
		Region[r].CheckArrivedMotorCycles();
	}
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


void Restaurant::AddOrderToVIP(Order *newOrd)

{
	switch( newOrd->GetRegion() )
	{
	    case A_REG :	
			this->Region[0].AddToVIPOrders(newOrd);
			break;
		case B_REG :
			this->Region[1].AddToVIPOrders(newOrd);
			break;
		case C_REG :
			this->Region[2].AddToVIPOrders(newOrd);
			break;
		case D_REG :
			this->Region[3].AddToVIPOrders(newOrd);
			break;
	}
}



void Restaurant::AddOrderToNormal(Order *newOrd)

{
	switch( newOrd->GetRegion() )
	{
	    case A_REG :	
			this->Region[0].AddToNormalOrders(newOrd);
			break;
		case B_REG :
			this->Region[1].AddToNormalOrders(newOrd);
			break;
		case C_REG :
			this->Region[2].AddToNormalOrders(newOrd);
			break;
		case D_REG :
			this->Region[3].AddToNormalOrders(newOrd);
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
			this->Region[0].AddToFrozenOrders(newOrd);
			break;
		case B_REG :
			this->Region[1].AddToFrozenOrders(newOrd);
			break;
		case C_REG :
			this->Region[2].AddToFrozenOrders(newOrd);
			break;
		case D_REG :
			this->Region[3].AddToFrozenOrders(newOrd);
			break;
	}
}



 

int Restaurant::GetPromotionLimit(int Max)
{
	return Max;
}



void Restaurant::RemoveNormalOrder(Order* remOrd)

{

	// --> Execute Remove fn. of NormalOrders list
	REGION RORD = remOrd->GetRegion();
	
	switch(RORD)
	{
	    case A_REG :	
			this->Region[0].CancelNormalOrder(remOrd->GetID());
			break;
		case B_REG :
			this->Region[1].CancelNormalOrder(remOrd->GetID());
			break;
		case C_REG :
			this->Region[2].CancelNormalOrder(remOrd->GetID());
			break;
		case D_REG :
			this->Region[3].CancelNormalOrder(remOrd->GetID());
			break;
	}
	//DEMO_Queue.dequeue(remOrd);

	///HMANA6399 :: I left this line for testing

}


void Restaurant::RemoveNormalOrderById(int Id){
	

	for (int i = 0; i < 4; i++)
	{
		this->Region[i].CancelNormalOrder(Id);
	}
	
}


// Marait:: under construction
Order* Restaurant::GetNormalOrderById(int ID){

	for (int i = 0; i < 4; i++)
	{
		Order* isThere = this->Region[i].GetNormalOrder(ID);
		if(isThere != NULL){
			return isThere;
		}
	}

	return NULL;
}

void Restaurant::InterActive()
{
	pGUI->PrintMessage("InterActive Mode , Mouse Click to Continue");
	pGUI->waitForClick();
	Load = new LoadAction("",this);
	
	do {
		pGUI->PrintMessage(!isLoaded ? 
			"Please enter a valid file name , Mouse Click to Continue" :
			"Please enter file to load , Mouse Click to Continue"
		);
		pGUI->waitForClick();
	
		LoadedFile = pGUI->GetString();
		if (LoadedFile.find(".txt") == -1) LoadedFile += ".txt";
	
		Load->setLoadFileName(LoadedFile);
		Load->Execute();	// first load the file 
		
	} while (!isLoaded);

	this->ProcessInterActive(); // second do the interactive stuff

	pGUI->PrintMessage("Choose A File To Save :  ");
	Save = new SaveAction( "" , this );//, this->AllOrders
	pGUI->waitForClick();
	
	SaveFile = pGUI->GetString();
	if (SaveFile.find(".txt") == -1) SaveFile += ".txt";	
	Save->setSaveFileName(SaveFile);

	Save->Execute(AllOrders); // do the save stuff
}

void Restaurant::IncreaseCurrentTime()
{
	this->CurrentTimeStep ++;
}

int Restaurant::GetCurrentTimeStep() const
{
	return this->CurrentTimeStep;
}

void Restaurant::ProcessInterActive()
{
	bool finishedServing = true;
	while (!this->EventsQueue.isEmpty() || finishedServing)  // this is the event loop where every order gets assigned to a motor cycle
	{
		IncreaseCurrentTime();
		this->ExecuteEvents(CurrentTimeStep);
		// here you print the number of active order type those in the list of orders
		this->pGUI->UpdateInterface(this);
		pGUI->PrintMessage(
			"Number of active {A:" + tostring(this->Region[0].GetNumberOfWaitingOrders()) +
			", B:" + tostring(this->Region[1].GetNumberOfWaitingOrders()) +
			", C:" + tostring(this->Region[2].GetNumberOfWaitingOrders()) +
			", D:" + tostring(this->Region[3].GetNumberOfWaitingOrders()) +
			"}" + "Number of motors [Z,N,F]"
			+ "  A[" + tostring(this->Region[0].GetFrozenMotorCount()) + "," + tostring(this->Region[0].GetNormalMotorCount()) + "," + tostring(this->Region[0].GetFastMotorCount()) + "]"
			+ ", B[" + tostring(this->Region[1].GetFrozenMotorCount()) + "," + tostring(this->Region[1].GetNormalMotorCount()) + "," + tostring(this->Region[1].GetFastMotorCount()) + "]"
			+ ", C[" + tostring(this->Region[2].GetFrozenMotorCount()) + "," + tostring(this->Region[2].GetNormalMotorCount()) + "," + tostring(this->Region[2].GetFastMotorCount()) + "]"
			+ ", D[" + tostring(this->Region[3].GetFrozenMotorCount()) + "," + tostring(this->Region[3].GetNormalMotorCount()) + "," + tostring(this->Region[3].GetFastMotorCount()) + "]" +
			"Mouse Click To increase TimeStep"
		);

		Sleep(1000);

		this->CheckArrivedMotorCycles();
		finishedServing = this->ServeAvailableOrders();

		pGUI->PrintMessage("Mouse Click To increase TimeStep");
	}
}

void Restaurant::StepByStep()
{
	pGUI->PrintMessage("StepByStep Mode , Mouse Click to Continue");
	pGUI->waitForClick();
	Load = new LoadAction("", this);

	do {
		pGUI->PrintMessage(!isLoaded ?
			"Please enter a valid file name , Mouse Click to Continue" :
			"Please enter file to load , Mouse Click to Continue"
		);
		pGUI->waitForClick();

		LoadedFile = pGUI->GetString();
		if (LoadedFile.find(".txt") == -1) LoadedFile += ".txt";

		Load->setLoadFileName(LoadedFile);
		Load->Execute();	// first load the file 

	} while (!isLoaded);


	this->ProcessStepByStep(); // second do the interactive stuff

	pGUI->PrintMessage("Choose A File To Save :  ");
	Save = new SaveAction("", this);//, this->AllOrders
	pGUI->waitForClick();

	SaveFile = pGUI->GetString();
	if (SaveFile.find(".txt") == -1) SaveFile += ".txt";
	Save->setSaveFileName(SaveFile);

	Save->Execute(AllOrders); // do the save stuff

	//Sleep(1000); // wait 1 second for the next function call
}

void Restaurant::ProcessStepByStep()
{
	bool finishedServing = true;

	while (!this->EventsQueue.isEmpty() || finishedServing)  // this is the event loop where every order gets assigned to a motor cycle
	{

		IncreaseCurrentTime();
		this->ExecuteEvents(CurrentTimeStep);
		// here you print the number of active order type those in the list of orders
		this->pGUI->UpdateInterface(this);
		pGUI->PrintMessage(
			"Number of active {A:" + tostring(this->Region[0].GetNumberOfWaitingOrders()) +
			", B:" + tostring(this->Region[1].GetNumberOfWaitingOrders()) +
			", C:" + tostring(this->Region[2].GetNumberOfWaitingOrders()) +
			", D:" + tostring(this->Region[3].GetNumberOfWaitingOrders()) +
			"}" + "Number of motors [Z,N,F]"
			+ "  A[" + tostring(this->Region[0].GetFrozenMotorCount()) + "," + tostring(this->Region[0].GetNormalMotorCount()) + "," + tostring(this->Region[0].GetFastMotorCount()) + "]"
			+ ", B[" + tostring(this->Region[1].GetFrozenMotorCount()) + "," + tostring(this->Region[1].GetNormalMotorCount()) + "," + tostring(this->Region[1].GetFastMotorCount()) + "]"
			+ ", C[" + tostring(this->Region[2].GetFrozenMotorCount()) + "," + tostring(this->Region[2].GetNormalMotorCount()) + "," + tostring(this->Region[2].GetFastMotorCount()) + "]"
			+ ", D[" + tostring(this->Region[3].GetFrozenMotorCount()) + "," + tostring(this->Region[3].GetNormalMotorCount()) + "," + tostring(this->Region[3].GetFastMotorCount()) + "]" +
			"Mouse Click To increase TimeStep"
		);

		Sleep(1000); // wait 1 second for the next function call

		this->CheckArrivedMotorCycles();
		finishedServing = this->ServeAvailableOrders();

		finishedServing = this->ServeAvailableOrders();
	}
	//Save->Execute();
}

void Restaurant::Silent()
{

	pGUI->PrintMessage("Silent Mode , Mouse Click to Continue");
	pGUI->waitForClick();
	Load = new LoadAction("", this);

	do {
		pGUI->PrintMessage(!isLoaded ?
			"Please enter a valid file name , Mouse Click to Continue" :
			"Please enter file to load , Mouse Click to Continue"
		);
		pGUI->waitForClick();

		LoadedFile = pGUI->GetString();
		if (LoadedFile.find(".txt") == -1) LoadedFile += ".txt";

		Load->setLoadFileName(LoadedFile);
		Load->Execute();	// first load the file 

	} while (!isLoaded);

	this->ProcessSilent(); // second do the interactive stuff

	pGUI->PrintMessage("Choose A File To Save :  ");
	Save = new SaveAction("", this);//, this->AllOrders
	pGUI->waitForClick();

	SaveFile = pGUI->GetString();
	if (SaveFile.find(".txt") == -1) SaveFile += ".txt";
	Save->setSaveFileName(SaveFile);

	Save->Execute(AllOrders); // do the save stuff

}

void Restaurant::ProcessSilent()
{

	bool finishedServing = true;

	while (!this->EventsQueue.isEmpty() || finishedServing)  // this is the event loop where every order gets assigned to a motor cycle
	{

		IncreaseCurrentTime();
		this->ExecuteEvents(CurrentTimeStep);
		// here you print the number of active order type those in the list of orders
		this->pGUI->UpdateInterface(this);

		this->CheckArrivedMotorCycles();
		finishedServing = this->ServeAvailableOrders();

		finishedServing = this->ServeAvailableOrders();
	}

	pGUI->PrintMessage("finished silent simulation click to continue");
	pGUI->waitForClick();
}

void Restaurant::AddToAllOrders(Order *Ord)
{
	pGUI->AddOrderForDrawing(Ord);

}

void Restaurant::RemoveFromAllOrders(Order *Ord){

	pGUI->RemoveOrderForDrawing(Ord);
}




/////////////////////////////////////////////////////
// Functions for Phase 2
////////////////////////////////////////////////////
bool Restaurant::AddOrderToPQ(Order* pOrd)
{
	Pair<int, Order*> t_pair(-1 * pOrd->getFinishTime(), pOrd);
	return this->AllOrders.enqueue(t_pair);
}


//Order Service
bool Restaurant::ServeAvailableOrders()
{
	bool finished = false;
	//Call the function	ServeAvailableOrders() of all regions
	for (int i = 0; i < 4; ++i){
		finished |= Region[i].ServeAvailableOrders(this) | Region[i].DidFinish();
	}
	//this->DeleteOrdersPerTS();
	return finished; //false when everything is done!

	//When you call the function in the simulation, Run the loop untill this function returns false
	//I better suggest this piece of code
	/*do {
		//Checking arrived motorcycles
		//Running the Events of this TS
		//Any other simulation code
	} while (ServeAvailableOrders());
	*/
}


void Restaurant::LoadFromFile(string fileName){
	fileName = "../input_files/" + fileName;
	ifstream LoadFile(fileName); //assigns and tries to open the file
	if (LoadFile.is_open()) 
	{
			isLoaded = true;
			string line;
		    int Froz , Nrm , Fst; 
			int Fst_Count , Nrm_Count , Froz_Count;
			LoadFile >> Froz >> Nrm >> Fst;

			this->MotorcycleSpeeds[Normal] = Nrm;
			this->MotorcycleSpeeds[Fast] = Fst;
			this->MotorcycleSpeeds[Frozen] = Froz;
			
			for( int i = 0 ; i < 4 ; i++)
			{
				LoadFile >> Nrm_Count >> Froz_Count >> Fst_Count;
				int j;
				//Adding Normal Motorcycles' Objects
				for (j = 0; j < Nrm_Count; ++j) {
					Region[i].AddMotorCycle(
						new Motorcycle(
							this->MotorcycleSpeeds[Normal],
							(REGION)i,
							Normal
						)
					);
				}
				//Adding Fast Motorcycles' Objects
				for (j = 0; j < Fst_Count; ++j) {
					Region[i].AddMotorCycle(
						new Motorcycle(
						this->MotorcycleSpeeds[Fast],
							(REGION)i,
							Fast
						)
					);
				}
				for (j = 0; j < Froz_Count; ++j) {
					Region[i].AddMotorCycle(
						new Motorcycle(
						this->MotorcycleSpeeds[Frozen],
							(REGION)i,
							Frozen
						)
					);
				}

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


						 Event *pEvent = new ArrivalEvent(TS,ID,O_Type,R_Type,MON,DST);
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
			
		} else isLoaded = false;
}
	

void Restaurant::SetPromotionTimeStep(int P_TimeSkip)
{
	this->AutoPromoteTimeStep = P_TimeSkip;
}

void Restaurant::addToDeletedPerTS(Order* pOrd)
{
	ordersToDeletePerTS.enqueue(pOrd);
}


void Restaurant::DeleteOrdersPerTS()
{
	Order* tOrd;
	while (!ordersToDeletePerTS.isEmpty())
	{
		ordersToDeletePerTS.dequeue(tOrd);
		RemoveFromAllOrders(tOrd);
	}
}

bool Restaurant::GetOrderToSave(Pair<int ,Order*> & Ord)
{
	if (this->AllOrders.isEmpty())
	{
		return false;

		Ord.setSecond(NULL);
	}
	Vector<Pair<int, Order*>> temp;

	Pair<int, Order*> SavedOrder;

	AllOrders.peekFront(SavedOrder);
	AllOrders.dequeue();
	temp.insert(SavedOrder);


	AllOrders.peekFront(SavedOrder);
	while (SavedOrder.getSecond()->getFinishTime() == temp[0].getSecond()->getFinishTime()) {
		AllOrders.dequeue();
		temp.insert(SavedOrder);
		if (AllOrders.isEmpty())
			break;
		AllOrders.peekFront(SavedOrder);
	}

	// no the temp has all orders with the same finish time
	// here do the comparison staff
	Pair<int, Order*> ordToSave = temp[0];

	
	for (size_t i = 1; i < temp.getSize() ; i++)
	{
		if (temp[i].getSecond()->getServTime() < ordToSave.getSecond()->getServTime()) {
			ordToSave = temp[i];
		}
	}

	// i should then return those that weren't used

	for (size_t i = 0; i < temp.getSize(); i++)
	{
		if (ordToSave.getSecond()->GetID() != temp[i].getSecond()->GetID()) {
			AllOrders.enqueue(temp[i]);
		}
	}

	Ord = ordToSave;

	return true;
}
