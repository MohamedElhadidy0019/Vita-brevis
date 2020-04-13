#pragma once
#include <fstream>
#include "DynBag.h"
#include "Rest\Cook.h"

class Kitchen
{
	DynamicBag<Cook*> activeVIPs, restingVIPs,
				      activeNormals, restingNormals,
					  activeVegans,  restingVegans;
	
	int num_cooks;

	void createNormalCooks(int, int, int);
	void createVeganCooks(int, int, int);
	void createVIPCooks(int, int, int);
	
public:
	Kitchen();
	void loadCooksFromFile(std::ifstream&);
	Cook** toArray();

	int getNumCooks();
	int getActiveNormalCooks();
	int getActiveVIPCooks();
	int getActiveVeganCooks();

	~Kitchen();
};

