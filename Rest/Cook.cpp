#include "Cook.h"

int Cook::NumOrdersBeforeBreak;
Cook::Cook()
{
}

Cook::Cook(int id, ORD_TYPE t, int Speed, int BreakDuration)
{
	ID = id;
	type = t;
	speed = Speed;
	breakDuration = BreakDuration;

	breakCounter = 0;
	dishesFinished = 0;
}


Cook::~Cook()
{
}


int Cook::GetID() const
{
	return ID;
}


ORD_TYPE Cook::GetType() const
{
	return type;
}


void Cook::setID(int id)
{
	ID = (id > 0)?id:-1;
}

void Cook::setType(ORD_TYPE t)
{
	type = t;
}

void Cook::setNumOrdersBeforeBreak(int x)
{
	NumOrdersBeforeBreak = (x > 0) ? x : 0;
}


