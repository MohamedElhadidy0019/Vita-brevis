#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, int totalNumDishes, double totalMoney, int ArrTime)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	status = WAIT;

	this->totalNumDishes = totalNumDishes;
	this->totalMoney = totalMoney;
	this->ArrTime = ArrTime;

	this->ServTime = 0 ;
	this->WaitTime = 0 ;
	this->finishedNumDishes = 0;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}


void Order::setStatus(ORD_STATUS s)
{
	status = s;
}

ORD_STATUS Order::getStatus() const
{
	return status;
}

void Order::promoteToVIP(double extraMoney)
{
	if (type == TYPE_NRM) {
		type = TYPE_VIP;
		if (extraMoney > 0) totalMoney += extraMoney;
	}
}

void Order::Wait()
{
	if(status == WAIT ) WaitTime++;
}

void Order::Service(int numDishes)
{
	if (status == SRV) {
		ServTime++;
		finishedNumDishes += numDishes;
		if (finishedNumDishes > totalNumDishes) status = DONE;
	}
}



int Order::getArrivalTime()
{
	return ArrTime;
}

int Order::getFinishTime()
{
	return ArrTime + WaitTime + ServTime;
}

int Order::getAssignmentTime()
{
	return ArrTime + WaitTime;
}

double Order::getMoney()
{
	return totalMoney;
}

int Order::getSize()
{
	return totalNumDishes;
}

