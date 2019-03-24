//#include "Drawing.h"

#include "Rest\Restaurant.h"

#include "GUI\GUI.h"

#include<iostream>
using namespace std;

int main()

{

	Restaurant* pRest = new Restaurant;

	pRest->RunSimulation();

	pRest->Just_A_Demo();


	cin.get();

	cin.ignore();



	delete pRest;

	

	return 0;

}