#include "LoadAction.h"
#include "Rest\Restaurant.h"


	
LoadAction::LoadAction(string LoadedFile, Restaurant * R)
{
	loadFileName = LoadedFile;
	pRest = R;
}

void LoadAction::Execute()
{	

	//this code should make sure that the file already exists before calling the restaurant function to do the loading stuff
	pRest->LoadFromFile( loadFileName ); // use temploadfromfile untill fixing loadfromfile
	//ifstream *LoadFile = new ifstream(loadFileName, ios::in); //assigns and tries to open the file
	
	
}

void LoadAction::setLoadFileName(string fname)
{
	this->loadFileName = fname;
}

LoadAction::~LoadAction(void)
{

}