#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int eTime, int oID, double Exmoney) : Event(eTime,oID)
{
	extraMoney = Exmoney;
}

PromotionEvent::PromotionEvent()
{
}

void PromotionEvent::readInfo(std::ifstream& file)
{
	file >> Event::EventTime >> Event::OrderID >> extraMoney;
}

void PromotionEvent::Execute(Restaurant* pRest)
{
	//TODO: ADD ACTUAL BEHAVIOUR IN PHASE 2


	//NO DEMO BEHAVIOUR
}
