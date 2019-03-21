#include "LoadAction.h"
#include "Rest\Restaurant.h"


LoadAction::LoadAction(string LoadedFile)
{	
	loadFileName = LoadedFile;
}
	
void LoadAction::Execute()
{	
	pRest->LoadFromFile( loadFileName );
	//ifstream *LoadFile = new ifstream(loadFileName, ios::in); //assigns and tries to open the file
	/*if (LoadFile->is_open()) 
	{
		
		while( !(LoadFile->eof()) )
		{
		    int Froz , Nrm , Fst;   
			cin >> Froz >> Nrm >> Fst;
			
			
			5 3 1  ➔ no. of motorcycles in Region A 
			6 3 2  ➔ no. of motorcycles in Region B 
			4 2 1  ➔ no. of motorcycles in Region C 
			9 4 2  ➔ no. of motorcycles in Region D 
		   
			int PromotionLimit; 
			cin >> PromotionLimit;
			
			
			
			int EventNumber; 
			cin >> EventNumber; 

			char EventType;
			int i = 0;

		    int R , TS , TYP , ID , DST , MON , REG;
			 Arrival event line have the following info R TS TYP ID DST MON  REG 
			  where R means an arrival event, TYP is the order type (N: normal, F: frozen, V: VIP). TS is the arrival time step. 
			  The ID is a unique sequence number that identifies each order. 
			  DST is the distance (in meters) between the order delivery location and the restaurant, 
			  MON is the total order money and REG is the order region.  
			 
			  Cancellation event line have the following info X TS ID 
			
			  where X means an order cancellation event occurring at time TS, and ID is the id of the order to be canceled. This ID must be of a Normal order. ❑ 
			  
			  Promotion event line have the following info P TS ID ExMon
			  
			  where P means an order promotion event occurring at time TS,and ID is the id of the order to be promoted to be VIP. This ID must be of a Normal order. 
			  ExMon if the extra money the customer paid for promotion
			  

			while( !(LoadFile->eof()) )
			{
				cin>>EventType;

				switch (EventType)
				{
				      case 'R':
						    break;
					  case 'N':
						    break;
					  case 'V':
						  break;
					  case 'F':
						  break;
			          default :
						    break;
				}
			}
			
			8       ➔ no. of events in this file 
			R 7 N 1 15 110 A  ➔ Arrival event 
			R 9 N 2 7 56 B 
			R 9 V 3 21 300 B 
			R 12 F 4 53 42 C 
			X 15 1     ➔ Cancellation event 
			R 19 N 5 17 95 D 
			P 19 2 62    ➔ promotion event 
			R 25 F 6 33 127 D 
		}
	}*/
	
}

LoadAction::~LoadAction(void)
{

}