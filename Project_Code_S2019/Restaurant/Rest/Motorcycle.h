#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	static int ID ;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	MotorcycleType Moto_Type; //Normal ,FROZEN AND Fast
	

public:
	Motorcycle();
	
	/////////////Setters And Getters

	void SetSpeed(int S,MotorcycleType M);
	int GetSpeed();

	void SetRegion(REGION R);
	REGION GetRegion();

	void SetStatus(STATUS ST);
	STATUS GetStatus();
	
	void SetOrder(ORD_TYPE O);
	ORD_TYPE GetOrder();

	virtual ~Motorcycle();
};

#endif