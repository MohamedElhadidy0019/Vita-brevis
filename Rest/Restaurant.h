#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_
#include <fstream>

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\Queue.h"
#include "..\DynList.h"
#include "..\Events\Event.h"

#include "..\Kitchen.h"
#include "Order.h"

// it is the maestro of the project
class Restaurant
{
private:
	GUI* pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	

	Queue<Order*> ServicingList;
	Queue<Order*> Finished;


	// TODO: Add More Data Members As Needed
	Kitchen Kitch;
	int autoPlimit;

	int NumWaitingOrders[TYPE_CNT];
	Queue<Order*> NRM_Orders;
	Queue<Order*> VGAN_Orders;
	QueuePriority<Order*> VIP_Orders;
	
	Event* CreateSpecificEvent(char);

	QueuePriority<Order*>* SortWaitingOrdersByArrival();

	int    CaclulateVIPPriorty(Order*);

	void UpdateOrderTimes();

	void MoveWaitingOrdersToServiceList();

	void MoveServicedOrdersToFinishedList();

public:

	Restaurant();
	~Restaurant();

	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	void FillDrawingList();

	//
	// TODO: Add More Member Functions As Needed
	//

	bool loadEventsAndCooksFromFile(string);
	void loadEventsFromFile(std::ifstream&);

	void Simulate();	//Simulation



	void PrintWaitingOrdersInformation();
	void PrintAvilableCooksInformation();



	void AddtoVIP_Queue(Order* pOrd);	//adds an order to the queue
	void AddtoNormal_Queue(Order* pOrd);	//adds an order to the queue
	void AddtoVegan_Queue(Order* pOrd);	//adds an order to the queue
	

	/// ================================================================================================== 
	void RemoveFromNormalQueue(int id);



};

#endif