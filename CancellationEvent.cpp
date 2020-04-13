#include "CancellationEvent.h"
#include "Rest\Restaurant.h"
CancellationEvent::CancellationEvent(int eTime, int oID) : Event(eTime, oID)
{
}

CancellationEvent::CancellationEvent()
{
}

void CancellationEvent::readInfo(std::ifstream& file)
{
	file >> Event::EventTime >> Event::OrderID;
}

void CancellationEvent::Execute(Restaurant* pRest)
{
	pRest->RemoveFromNormalQueue(Event::OrderID);
}
