#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	MotorcycleType Moto_Type; //Normal ,FROZEN AND Fast
	
	int DeliveryTime;
	// at assignment time of the motor to an order i will set the time untill delivery to (distance/speed)*2 and at each time step i will decrement the time untill delivery by one time step

public:
	Motorcycle();
	Motorcycle(int sp, REGION reg, MotorcycleType mc_type);
	
	/////////////Setters And Getters

	void SetSpeed(int S,MotorcycleType M);
	int GetSpeed();

	void SetRegion(REGION R);
	REGION GetRegion();

	void SetStatus(STATUS ST);
	STATUS GetStatus();
	
	MotorcycleType GetType();

	//Function for Delivery Time
	int GetTimeUntillDelivery();
	void SetTimeUntillDelivery(int td);
	bool DecrementDeliveryTime();
	
	virtual ~Motorcycle();
};

#endif