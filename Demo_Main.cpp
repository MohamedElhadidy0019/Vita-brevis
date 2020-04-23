//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"

int main()
{
	//m4 fahem
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	delete pRest;
	
	return 0;
}
