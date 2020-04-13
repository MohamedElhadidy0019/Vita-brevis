#pragma once
#include ".\Events\Event.h"
class PromotionEvent :
	public Event
{
private:
	double extraMoney;
public:
	PromotionEvent(int eTime, int oID, double Exmoney);
	PromotionEvent();
	void readInfo(std::ifstream&);
	void Execute(Restaurant* pRest);
};

