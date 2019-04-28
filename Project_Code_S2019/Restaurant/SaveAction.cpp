#include "SaveAction.h"
#include "Rest\Restaurant.h"

SaveAction::SaveAction( string SavedFile , Restaurant* P)
{
	//this->ALLRestOrders = AllOrders;
	this->SaveFileName = SavedFile;
	pRest = P;
}
void SaveAction::setSaveFileName(string fname)
{
	this->SaveFileName = fname;
}
void SaveAction::Execute(priority_q<Pair<int, Order*>> ALLRestOrders)
{
	Pair<int, Order*> SavedOrder ;
	
	float CountOrdA = pRest->GetRegion(A_REG).GetOrderCount();
	float CountOrdB = pRest->GetRegion(B_REG).GetOrderCount();
	float CountOrdC = pRest->GetRegion(B_REG).GetOrderCount();
	float CountOrdD = pRest->GetRegion(B_REG).GetOrderCount();
	float ALLOrderCount = CountOrdA + CountOrdB + CountOrdC + CountOrdD;
	
	
	float CountNrmOrderA = 0 , CountNrmOrderB = 0;
	float CountFrzOrderA = 0 , CountFrzOrderB = 0;
	float CountVipOrderA = 0 , CountVipOrderB = 0;

	float CountNrmOrderC = 0 , CountNrmOrderD = 0;
	float CountFrzOrderC = 0 , CountFrzOrderD = 0;
	float CountVipOrderC = 0   , CountVipOrderD = 0;
	
	////////////////////////////////////////////////////////////////////////
	float CountFstMotorA = pRest->GetRegion(A_REG).GetFastMotorCount();
	float CountNrmMotorA = pRest->GetRegion(A_REG).GetNormalMotorCount();
	float CountFrzMotorA = pRest->GetRegion(A_REG).GetFrozenMotorCount();
	float ALLMotorCountA = CountFstMotorA + CountNrmMotorA + CountFrzMotorA;

	float CountFstMotorB = pRest->GetRegion(B_REG).GetFastMotorCount();
	float CountNrmMotorB = pRest->GetRegion(B_REG).GetNormalMotorCount();
	float CountFrzMotorB = pRest->GetRegion(B_REG).GetFrozenMotorCount();
	float ALLMotorCountB = CountFstMotorB + CountNrmMotorB + CountFrzMotorB;

	float CountFstMotorC = pRest->GetRegion(C_REG).GetFastMotorCount();
	float CountNrmMotorC = pRest->GetRegion(C_REG).GetNormalMotorCount();
	float CountFrzMotorC = pRest->GetRegion(C_REG).GetFrozenMotorCount();
	float ALLMotorCountC = CountFstMotorC + CountNrmMotorC + CountFrzMotorC;

	float CountFstMotorD = pRest->GetRegion(D_REG).GetFastMotorCount();
	float CountNrmMotorD = pRest->GetRegion(D_REG).GetNormalMotorCount();
	float CountFrzMotorD = pRest->GetRegion(D_REG).GetFrozenMotorCount();
	float ALLMotorCountD = CountFstMotorD + CountNrmMotorD + CountFrzMotorD;

	float ALLMotors = ALLMotorCountA + ALLMotorCountB + ALLMotorCountC + ALLMotorCountD;
	float ALLNrmMotors = CountNrmMotorA + CountNrmMotorB + CountNrmMotorC + CountNrmMotorD;
	float ALLFstMotors = CountFstMotorA + CountFstMotorB + CountFstMotorC + CountFstMotorD;
	float ALLFrzMotors = CountFrzMotorA + CountFrzMotorB + CountFrzMotorC + CountFrzMotorD;

	int ServTimeA = pRest->GetRegion(A_REG).GetTotalServTime();
	int ServTimeB = pRest->GetRegion(B_REG).GetTotalServTime();
	int ServTimeC = pRest->GetRegion(C_REG).GetTotalServTime();
	int ServTimeD = pRest->GetRegion(D_REG).GetTotalServTime();

	int TotalServ = ServTimeA + ServTimeB + ServTimeC + ServTimeD;

	int WaitTimeA = pRest->GetRegion(A_REG).GetTotalWaitingTime();
	int WaitTimeB = pRest->GetRegion(B_REG).GetTotalWaitingTime();
	int WaitTimeC = pRest->GetRegion(C_REG).GetTotalWaitingTime();;
	int WaitTimeD = pRest->GetRegion(D_REG).GetTotalWaitingTime();;

	int TotalWait = WaitTimeA + WaitTimeB + WaitTimeC + WaitTimeD;
	OutFile.open(this->SaveFileName);

	while(ALLRestOrders.peekFront(SavedOrder))
	{
		OutFile << "FT ID AT  WT ST\n"
			    << SavedOrder.getSecond()->getFinishTime()
				<<  SavedOrder.getSecond()->GetID()
				<<  SavedOrder.getSecond()->getArrTime()
				<<  SavedOrder.getSecond()->getWaitingTime()
				<<  SavedOrder.getSecond()->getServTime() <<"\n";
		switch(SavedOrder.getSecond()->GetRegion())
		{
		     case A_REG:
		          switch(SavedOrder.getSecond()->GetType())
		          {
		             case TYPE_NRM:
						 CountNrmOrderA ++;
		     	     case TYPE_FROZ:
						 CountFrzOrderA ++;
                     case TYPE_VIP:
						 CountVipOrderA ++;
		          }
			 case B_REG:
				  switch(SavedOrder.getSecond()->GetType())
		          {
		             case TYPE_NRM:
						 CountNrmOrderB ++;
		     	     case TYPE_FROZ:
						 CountFrzOrderB ++;
                     case TYPE_VIP:
						 CountVipOrderB ++;
		          }
			 case C_REG:
				  switch(SavedOrder.getSecond()->GetType())
		          {
		             case TYPE_NRM:
						 CountNrmOrderC ++;
		     	    case TYPE_FROZ:
						 CountFrzOrderC ++;
                     case TYPE_VIP:
						 CountVipOrderC ++;
		          }
			 case D_REG:
				  switch(SavedOrder.getSecond()->GetType())
		          {
		             case TYPE_NRM:
						 CountNrmOrderD ++;
		     	     case TYPE_FROZ:
						 CountFrzOrderD ++;
                     case TYPE_VIP:
						 CountVipOrderD ++;
		          }
		}

	}
	float ALLNrmOrderCount = CountNrmOrderA + CountNrmOrderB + CountNrmOrderC + CountNrmOrderD;
	float ALLVipOrderCount = CountVipOrderA + CountVipOrderB + CountVipOrderC + CountVipOrderD;
	float ALLFrzOrderCount = CountFrzOrderA + CountFrzOrderB + CountFrzOrderC + CountFrzOrderD;


	OutFile<<"Region A:\n"
		   <<"Orders:"<< CountOrdA <<"[Norm:"<< CountNrmOrderA <<", Froz:"<< CountFrzOrderA <<", VIP:"<< CountVipOrderA <<"]"  
		   <<"MotorCount:"<< ALLMotorCountA
		   <<"[Norm:"<< CountNrmMotorA <<", Froz:"<< CountFrzMotorA <<", Fast:"<< CountFstMotorA <<"]"
		   <<"Avg Wait = "<< WaitTimeA/ALLMotorCountA <<",  Avg Serv = "<< ServTimeA/ALLMotorCountA
		   
		   <<"\nRegion B:\n"
		   <<"Orders:"<< CountOrdB <<"[Norm:"<< CountNrmOrderB <<", Froz:"<< CountFrzOrderB <<", VIP:"<< CountVipOrderB <<"]"  
           <<"MotorCount:"<<  ALLMotorCountB
		   <<"[Norm:"<< CountNrmMotorB <<", Froz:"<< CountFrzMotorB <<", Fast:"<< CountFstMotorB <<"]"
		    <<"Avg Wait = "<< WaitTimeB/ALLMotorCountB <<",  Avg Serv = "<< ServTimeB/ALLMotorCountB
		   
		   <<"\nRegion C:\n"
		   <<"Orders:"<< CountOrdC <<"[Norm:"<< CountNrmOrderC <<", Froz:"<< CountFrzOrderC <<", VIP:"<< CountVipOrderC <<"]"  
           <<"MotorCount:"<< ALLMotorCountC
		   <<"[Norm:"<< CountNrmMotorC <<", Froz:"<< CountFrzMotorC <<", Fast:"<< CountFstMotorC <<"]"
		   <<"Avg Wait = "<< WaitTimeC/ALLMotorCountC <<",  Avg Serv = "<< ServTimeC/ALLMotorCountC
		   
		   <<"\nRegion D:\n"
		   <<"Orders:"<< CountOrdD <<"[Norm:"<< CountNrmOrderD <<", Froz:"<< CountFrzOrderD <<", VIP:"<< CountVipOrderD <<"]"
           <<"MotorCount:"<< ALLMotorCountD
		   <<"[Norm:"<< CountNrmMotorD <<", Froz:"<< CountFrzMotorD <<", VIP:"<< CountFstMotorD <<"]"
		   <<"Avg Wait = "<< WaitTimeD/ALLMotorCountD <<",  Avg Serv = "<< ServTimeD/ALLMotorCountD
		   
		   <<"\nRestaurant:\n"
		   <<"Orders:"<< ALLOrderCount <<"[Norm:" << ALLNrmOrderCount <<", Froz:"<< ALLFrzOrderCount <<", VIP:" << ALLVipOrderCount <<"]"   

		   <<"MotorCount:"<< ALLMotors  <<"[Norm:"<< ALLNrmMotors <<", Froz:"<< ALLFrzMotors <<", Fast:"<< ALLFstMotors <<"]"
		   <<"Avg Wait = "<< TotalWait/ALLMotors <<",  Avg Serv = "<< TotalServ/ALLMotors;

	
}

SaveAction::~SaveAction(void)
{

}