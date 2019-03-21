//#include "Drawing.h"

#include "Rest\Restaurant.h"

#include "GUI\GUI.h"

#include<iostream>
#include"Generic_DS/Vector.h"
using namespace std;

int main()

{

	{
	
		Vector<int> a;
		a.insert(3);
		a.insert(34);
		cout << a[0] << endl;
		cout << a[1] << endl;

	}

	Restaurant* pRest = new Restaurant;

	pRest->RunSimulation();



	pRest->Just_A_Demo();


	cin.get();

	cin.ignore();



	delete pRest;

	

	return 0;

}