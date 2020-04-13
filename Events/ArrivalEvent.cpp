#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"

ORD_TYPE ArrivalEvent::fromCharToOrder(char o) {
	return (o == 'N') ? TYPE_NRM :
		(o == 'G') ? TYPE_VGAN :
		(o == 'V') ? TYPE_VIP :
		TYPE_CNT;
}


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType) :Event(eTime, oID)
{
	OrdType = oType;
}

ArrivalEvent::ArrivalEvent()
{
}

void ArrivalEvent::readInfo(std::ifstream& file)
{
	char Ordtype;
	file >> Ordtype;
	OrdType = fromCharToOrder(Ordtype);
	int temp;
	file >> temp;
	Event::EventTime = temp;
	file >> temp;
	Event::OrderID = temp;
	file >> temp;
	OrdNumDishes = temp;
	file >> temp;
	OrdMoney = temp;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create an order and fills its data 
	// Then adds it to normal, vegan, or VIP order lists that you will create in phase1

	Order* pOrd = new Order(OrderID, OrdType, OrdNumDishes, OrdMoney, EventTime);
		
	if (OrdType == TYPE_NRM) {
		pRest->AddtoNormal_Queue(pOrd);
		//std::cout << "\nA NORMAL ORDER HAS ARRIVED\n";
	}
	else if (OrdType == TYPE_VGAN) {
		pRest->AddtoVegan_Queue(pOrd);
		//std::cout << "\nA VEGAN ORDER HAS ARRIVED\n";
	}
	else {
		pRest->AddtoVIP_Queue(pOrd);
		//std::cout << "\nA VIP ORDER HAS ARRIVED\n";
	}
}
