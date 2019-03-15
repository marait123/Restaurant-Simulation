#pragma once
#include "Event.h"
class PromoteEvent :
	public Event
{
	//info about the order related to arrival event
	int promotededOrderID;
	///HMANA6399 :: This shoulld always be an ID of a Normal Order, you should check this first
	///in the input stage.
	double extraMoney;
	///HMANA6399 :: double like that of ArrivalEvent
public:
	PromoteEvent(int eTime, int promOrdId, double exMon);
	void Execute(Restaurant* pRest);
	~PromoteEvent();
};

