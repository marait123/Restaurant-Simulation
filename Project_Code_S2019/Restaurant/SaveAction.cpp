#include "SaveAction.h"


SaveAction::SaveAction(void)
{

}

void SaveAction::Execute(ofstream &OutFile)
{
	OutFile<<"FT ID AT  WT ST\n"
		   <<""<<""<<""<<""

		   <<"Region A:\n"
		   <<"Orders:"<< 124 <<"[Norm:"<<100<<", Froz:"<<15<<", VIP:"<<9<<"]"  
           <<"MotorC:"<< 9   <<"[Norm:"<<5<<", Froz:"<<3<<", VIP:"<<1<<"]"
		   <<"Avg Wait = "<<12.3<<",  Avg Serv = "<< 25.65
		   
		   <<"\nRegion B:\n"
		   <<"Orders:"<< 124 <<"[Norm:"<<100<<", Froz:"<<15<<", VIP:"<<9<<"]"  
           <<"MotorC:"<< 9   <<"[Norm:"<<5<<", Froz:"<<3<<", VIP:"<<1<<"]"
		   <<"Avg Wait = "<<12.3<<",  Avg Serv = "<< 25.65
		   
		   <<"\nRegion C:\n"
		   <<"Orders:"<< 124 <<"[Norm:"<<100<<", Froz:"<<15<<", VIP:"<<9<<"]"  
           <<"MotorC:"<< 9   <<"[Norm:"<<5<<", Froz:"<<3<<", VIP:"<<1<<"]"
		   <<"Avg Wait = "<<12.3<<",  Avg Serv = "<< 25.65
		   
		   <<"\nRegion D:\n"
		   <<"Orders:"<< 124 <<"[Norm:"<<100<<", Froz:"<<15<<", VIP:"<<9<<"]"  
           <<"MotorC:"<< 9   <<"[Norm:"<<5<<", Froz:"<<3<<", VIP:"<<1<<"]"
		   <<"Avg Wait = "<<12.3<<",  Avg Serv = "<< 25.65
		   
		   <<"\nRestaurant:\n"
		   <<"Orders:"<< 124 <<"[Norm:"<<100<<", Froz:"<<15<<", VIP:"<<9<<"]"  
           <<"MotorC:"<< 9   <<"[Norm:"<<5<<", Froz:"<<3<<", VIP:"<<1<<"]"
		   <<"Avg Wait = "<<12.3<<",  Avg Serv = "<< 25.65;

		   
}

SaveAction::~SaveAction(void)
{

}