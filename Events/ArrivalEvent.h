#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include <iostream>
#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdNumDishes;	//order number of dishes
	ORD_TYPE OrdType;		//order type: Normal, vegan, VIP	                
	double OrdMoney;	//Total order money

	ORD_TYPE fromCharToOrder(char o);
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE oType);
	ArrivalEvent();
	//Add more constructors if needed

	void readInfo(std::ifstream&);
	void Execute(Restaurant *pRest);	//override execute function




	//Don't Mind this Debugging only
	void print() {
		cout << "Event ID:   " << OrderID << "      Arrival TIME:   " << EventTime;
		const char* type =  (OrdType == TYPE_NRM) ? "NORMAL"  :
							(OrdType == TYPE_VGAN) ? "VEGAN " : "VIP";
		cout << "Type :" << type;
	}
};

#endif