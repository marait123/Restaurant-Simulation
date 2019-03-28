
#pragma once

#include "Event.h"

class CancelEvent :

	public Event

{

	//info about the order related to arrival event

	int cancelledOrderID;

	///HMANA6399 :: This should always be an ID of a Normal Order ,  you  should  check  this  first

	///in the input stage. It should also has a Timestep than that of the Order to be cancelled

public:

	CancelEvent(int eTime, int cancelOrdID);

	void Execute(Restaurant* pRest);

	~CancelEvent();

};