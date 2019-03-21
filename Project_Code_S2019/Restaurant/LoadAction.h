#ifndef _LOADACTION_
#define _LOADACTION_

#include <iostream>
#include <string>
#include <fstream>

#include "GUI\GUI.h"


using namespace std;

class Restaurant;

class LoadAction
{
	ifstream* LoadFile;
	string loadFileName;
	GUI *pGUI;
	Restaurant *pRest;

    public:
	LoadAction(string LoadedFile );
	void Execute();
	~LoadAction(void);
};
#endif

