#include "Kitchen.h"
#include <iostream>

void Kitchen::createNormalCooks(int number, int speed, int breakDuration)
{
	Cook* temp;
	activeNormals.initializeCapacity(number);
	for (int i = 0; i < number; ++i) {
		num_cooks++;
		temp = new Cook(num_cooks, TYPE_NRM, speed, breakDuration);
		activeNormals.addElement(temp);
	}
}

void Kitchen::createVeganCooks(int number, int speed, int breakDuration)
{
	Cook* temp;
	activeVegans.initializeCapacity(number);
	for (int i = 0; i < number; ++i) {
		num_cooks++;
		temp = new Cook(num_cooks, TYPE_VGAN, speed, breakDuration);
		activeVegans.addElement(temp);
	}
}

void Kitchen::createVIPCooks(int number, int speed, int breakDuration)
{
	Cook* temp;
	activeVIPs.initializeCapacity(number);
	for (int i = 0; i < number; ++i) {
		num_cooks++;
		temp = new Cook(num_cooks, TYPE_VIP, speed, breakDuration);
		activeVIPs.addElement(temp);
	}
}

Cook** Kitchen::toArray()
{

	Cook** Arr = new Cook* [num_cooks];
	
	int ArrIndex = 0;
	for (int i = 0; i < activeNormals.getSize(); ++i) {
		Arr[ArrIndex] = activeNormals.take();
		ArrIndex++;
	}
	for (int i = 0; i < activeVegans.getSize(); ++i) {
		Arr[ArrIndex] = activeVegans.take();
		ArrIndex++;
	}
	for (int i = 0; i < activeVIPs.getSize(); ++i) {
		Arr[ArrIndex] = activeVIPs.take();
		ArrIndex++;
	}
	for (int i = 0; i < restingNormals.getSize(); ++i) {
		Arr[ArrIndex] = restingNormals.take();
		ArrIndex++;
	}
	for (int i = 0; i < restingVegans.getSize(); ++i) {
		Arr[ArrIndex] = restingVegans.take();
		ArrIndex++;
	}
	for (int i = 0; i < restingVIPs.getSize(); ++i) {
		Arr[ArrIndex] = restingVIPs.take();
		ArrIndex++;
	}


	return Arr;
}

int Kitchen::getNumCooks()
{
	return num_cooks;
}

int Kitchen::getActiveNormalCooks()
{
	return activeNormals.getSize();
}

int Kitchen::getActiveVIPCooks()
{
	return activeVIPs.getSize();
}

int Kitchen::getActiveVeganCooks()
{
	return activeVegans.getSize();
}

Kitchen::Kitchen()
{
	num_cooks = 0;
}

void Kitchen::loadCooksFromFile(std::ifstream& file)
{
	int NormalCooksNo, VeganCooksNo, VIPCooksNo;
	int NormalCooksSpeed, VeganCooksSpeed, VIPCooksSpeed;
	int NumOrdersBeforeBreak;
	int BreakDurationNormal, BreakDurationVegan, BreakDurationVIP;

	file >> NormalCooksNo >> VeganCooksNo >> VIPCooksNo;

	file>> NormalCooksSpeed>>VeganCooksSpeed>>VIPCooksSpeed;

	file>> NumOrdersBeforeBreak;

	file>>BreakDurationNormal>>BreakDurationVegan>>BreakDurationVIP;

	Cook::setNumOrdersBeforeBreak(NumOrdersBeforeBreak);

	createNormalCooks(NormalCooksNo, NormalCooksSpeed, BreakDurationNormal);
	createVeganCooks(VeganCooksNo, VeganCooksSpeed, BreakDurationVegan);
	createVIPCooks(VIPCooksNo, VIPCooksSpeed, BreakDurationVIP);

}

Kitchen::~Kitchen()
{
}
