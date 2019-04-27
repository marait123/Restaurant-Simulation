#ifndef __ORDER_H_

#define __ORDER_H_



#include "..\Defs.h"



class Order

{



protected:

	int ID;         //Each order has a unique ID (from 1 --> 999 )

	ORD_TYPE type;		//order type: Normal, Frozen, VIP

	REGION Region;  //Region of this order

	int Distance;	//The distance (in meters) between the order location and the resturant 

	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime, WaitingTime;	//arrival, service start, and finish times
	

public:
	///<summary>you will send id r_type r_region </summary>
	Order(int id, ORD_TYPE r_Type, REGION r_region, int eTime, double ordMon =0 , double ordDist=0);
	virtual ~Order();

	int GetID();
	ORD_TYPE GetType() const;
	REGION GetRegion() const;
	int GetDistance() const;
	int GetArrivalTime() const;
	int getArrTime();
	int getServTime();
	int getFinishTime();

	void SetDistance(int d);
	void setWaitingTime(int t);
	void updateFinishTime();
	void setServTime(int t);

	///<summary>this operator returns if the left operand has a higher priority than the right</summary>
	///<param name ="od">this the right operand</param>
	bool operator >(const Order& od) const; /// INVERTED!!

	///<summary>this operator returns if the left operand has a less priority than the right</summary>
	///<param name ="od">this the right operand</param>
	bool operator <(const Order& od) const; /// INVERTED!!

	///<summary>this operator returns if the left operand has an equal priority to the right</summary>
	///<param name ="od">this the right operand</param>
	bool operator == (const Order&) const;


	///HMANA6399 :: Added by me in order to be easy for the Load stage to compare arrivalTime of

	///cancellation Event and the Order to be cancelled

	void IncreaseMoney(double ammount);

	void SetType(ORD_TYPE);

	///HMANA6399 :: Also added by me to increase money and change type in case of promotion

	double GetMoney();
};



#endif