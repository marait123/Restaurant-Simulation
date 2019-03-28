#pragma once

#include <fstream>
using namespace std;

class SaveAction
{
    public:
	SaveAction(void);
	void Execute(ofstream &OutFile);
	~SaveAction(void);
};

