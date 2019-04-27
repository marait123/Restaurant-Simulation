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
	isLoaded = true;
}


Restaurant::~Restaurant()
{
		delete pGUI;
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
	int EventCnt;	
	Order* pOrd;
	Event* pEv;

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
			+ ", D[" + tostring(this->Region[3].GetFrozenMotorCount()) + "," + tostring(this->Region[3].GetNormalMotorCount()) + "," + tostring(this->Region[3].GetFastMotorCount()) + "]"+
			"Mouse Click To increase TimeStep"
		);
		pGUI->waitForClick();

		pGUI->PrintMessage("Mouse Click To increase TimeStep");


		for (size_t i = 0; i < 4; i++)
		{
			Order** listOfOrd = NULL;
			for (size_t j = 0; j < 3; j++)
			{
				if (listOfOrd[j] != NULL) {
					pGUI->RemoveOrderForDrawing(listOfOrd[j]);
				}
			}
			delete[] listOfOrd;
		}
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

	pGUI->waitForClick();
	do {
		pGUI->PrintMessage(!isLoaded ?
			"Please enter a valid file name , Mouse Click to Continue" :
			"Please enter file to save , Mouse Click to Continue"
		);
		pGUI->waitForClick();

		SaveFile = pGUI->GetString();
		if (SaveFile.find(".txt") == -1) SaveFile += ".txt";

		// Save->setLoadFileName(SaveFile);
		// Save->Execute();	// Save the file 

	} while (!isLoaded);


	//Sleep(1000); // wait 1 second for the next function call
}

void Restaurant::ProcessStepByStep()
{
	while (!this->EventsQueue.isEmpty())  // this is the event loop where every order gets assigned to a motor cycle
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

		pGUI->PrintMessage("Mouse Click To increase TimeStep");

		//Excute Events;
		for (size_t i = 0; i < 4; i++)
		{
			Order** listOfOrd = NULL;
			this->Region[i].Phase1Delete(listOfOrd);
			for (size_t j = 0; j < 3; j++)
			{
				if (listOfOrd[j] != NULL) {
					pGUI->RemoveOrderForDrawing(listOfOrd[j]);
				}
			}
			delete[] listOfOrd;
		}

	}
	//Save->Execute();
}

void Restaurant::Silent()
{
	int EventCnt;	
	Order* pOrd;
	Event* pEv;

	pGUI->PrintMessage("Silent Mode , Mouse Click to Continue");
	pGUI->waitForClick();	
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


	/*here between the loading and the saving the simulation tekes action*/

	this->ProcessSilent();

	do {
		pGUI->PrintMessage(!isLoaded ?
			"Please enter a valid file name , Mouse Click to Continue" :
			"Please enter file to save , Mouse Click to Continue"
		);
		pGUI->waitForClick();

		SaveFile = pGUI->GetString();
		if (SaveFile.find(".txt") == -1) SaveFile += ".txt";

		// Save->setLoadFileName(SaveFile);
		// Save->Execute();	// Save the file 

	} while (!isLoaded);





}

void Restaurant::ProcessSilent()
{
	bool finishedServing = false;
	while (!this->EventsQueue.isEmpty() || !finishedServing)  // this is the event loop where every order gets assigned to a motor cycle
	{
		/*
			in this part of the simulation 
			1. i execute events in their order of arrival (cancellation - promotion - arrival)
		*/

		IncreaseCurrentTime();
		this->ExecuteEvents(CurrentTimeStep);		// the part of executing events is done as i see
		// here you print the number of active order type those in the list of orders
		this->pGUI->UpdateInterface(this);

		/*
			in this part of the simulation
			1. i should assign the orders to the motorcycles	
				// the steps to do this is that every region manager you check if it is still have
				// something to do if it has you call  a function to serve every order it can serv
				// if it doesn't you don't do anything untill each region manager as well has nothing 
				// to do and you end the simulation
			2. Check to see which motorcycle has come back 
			3. those orders that have been served i should move them to the list of served orders
			4. i should stay here untill i have no orders in any region that are waiting or haven't yet
			   been served			
		*/


		bool RegFinish[4] = { false, false, false, false };

	


		for (size_t i = 0; i < 4; i++)
		{
			RegFinish[i] = Region[i].DidFinish();
			finishedServing = finishedServing && RegFinish[i];
			if (!RegFinish[i]) {
				// Marait: important to read 
				// we could replace all the functions below by one big function that does all this or calls all this 
				// Region[i].ServeOrders();			// this function needs to be implemented in every region manager 
				// Region[i].IncrementTime();		// it decrement the time that every motorcycle will deliver its delivery in 
				// Region[i].checkArrival();		// this function should check if a motorcycle finished serving and if they have it should
				// it should move the orders that were on the motorcyles to the list of served orders where they will be sorted according to
				// their finish time 

			}
		}


	}
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
	return this->AllOrders.enqueue(pOrd);
}


//Assign an Order to a Motorcycle
bool Restaurant::ServeOrder(Order* pOrd)
{
	//Call the approperiate AssignOrderToMotorcyle fn according to the Region
	//TODO :: Decide if it's bool or void
	return Region[pOrd->GetRegion()].ServeOrder(pOrd);
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
				LoadFile >> Fst_Count >> Nrm_Count >> Froz_Count;
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
