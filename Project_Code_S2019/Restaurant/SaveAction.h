#ifndef _SAVEACTION_
#define _SAVEACTION_

#include "Generic_DS\priority_q.h"
#include "Generic_DS\Pair.h"
#include "Rest\Order.h"
#include "Defs.h"

#include <fstream>


using namespace std;

class Restaurant;

class SaveAction
{
	string SaveFileName;
	Restaurant *pRest;

    public:
	SaveAction( string SavedFile , Restaurant* );//  ,
	void setSaveFileName(string fname);
	void Execute(priority_q<Pair<int, Order*>> AllOrders);
	~SaveAction(void);
};
#endif
