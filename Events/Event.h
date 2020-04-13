#ifndef __EVENT_H_
#define __EVENT_H_

#include <iostream>
#include "..\Defs.h"
#include <fstream>
using namespace std;
class Restaurant;	//Forward declation

//The base class for all possible events in the system (abstract class)
class Event
{
protected:
	int EventTime;	//Timestep when this event takes place
	int OrderID;	//each event is related to certain order
public:
	Event(int eTime, int ordID);
	Event();

	int getEventTime();
	int getOrderID();
	virtual ~Event();

	virtual void readInfo(std::ifstream&) = 0;
	virtual void Execute(Restaurant* pRest)=0;	////a pointer to "Restaurant" and events need it to execute
	
	virtual void print() {

	}

};


#endif