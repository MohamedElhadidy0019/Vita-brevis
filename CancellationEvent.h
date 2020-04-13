#pragma once
#include ".\Events\Event.h"

class CancellationEvent :
	public Event
{

public:
	CancellationEvent(int eTime, int oID);
	CancellationEvent();
	void readInfo(std::ifstream&);
	void Execute(Restaurant* pRest);
};

