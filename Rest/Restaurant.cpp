#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\CancellationEvent.h"
#include "..\PromotionEvent.h"

//Takes the type of event as a character and returns a pointer to a dynamically created event of that type
Event* Restaurant::CreateSpecificEvent(char type)
{
	switch (type)
	{
	case 'R': return new ArrivalEvent();

	case 'X': return new CancellationEvent();

	case 'P': return new PromotionEvent();

	default: return nullptr;
	}
}

QueuePriority<Order*>* Restaurant::SortWaitingOrdersByArrival()
{
	QueuePriority<Order*>* SortedOrders = new QueuePriority<Order*>;
	Order** OrdersArr;

	int NormalOrdersCount;
	OrdersArr = NRM_Orders.toArray(NormalOrdersCount);
	for (int i = 0; i < NormalOrdersCount; i++) {
		SortedOrders->enqueue(OrdersArr[i], - OrdersArr[i]->getArrivalTime() );
	}
	delete[] OrdersArr;

	int VeganOrdersCount;
	OrdersArr = VGAN_Orders.toArray(VeganOrdersCount);
	for (int i = 0; i < VeganOrdersCount; i++) {
		SortedOrders->enqueue(OrdersArr[i], - OrdersArr[i]->getArrivalTime());
	}
	delete[] OrdersArr;

	int VIPOrdersCount;
	OrdersArr = VIP_Orders.toArray(VIPOrdersCount);
	for (int i = 0; i < VIPOrdersCount; i++) {
		SortedOrders->enqueue(OrdersArr[i], - OrdersArr[i]->getArrivalTime());
	}
	delete[] OrdersArr;

	
	return SortedOrders;
}

int Restaurant::CaclulateVIPPriorty(Order* o)
{
	return  ( o->getMoney() )  / 
								( 10*(o->getArrivalTime() ) + o->getSize() )  ;
		
}

void Restaurant::UpdateOrderTimes()
{
	Queue<Order*> tempQ;
	Order* temp;
	while (NRM_Orders.dequeue(temp)) {
		temp->Wait();
		tempQ.enqueue(temp);
	}
	while (tempQ.dequeue(temp)) NRM_Orders.enqueue(temp);

	while (VGAN_Orders.dequeue(temp)) {
		temp->Wait();
		tempQ.enqueue(temp);
	}
	while (tempQ.dequeue(temp)) VGAN_Orders.enqueue(temp);

	while (VIP_Orders.dequeue(temp)) {
		temp->Wait();
		tempQ.enqueue(temp);
	}
	while (tempQ.dequeue(temp)) VIP_Orders.enqueue(temp);



	while (ServicingList.dequeue(temp)) {
		temp->Service(0);
		tempQ.enqueue(temp);
	}
	while (tempQ.dequeue(temp)) ServicingList.enqueue(temp);

}

void Restaurant::MoveWaitingOrdersToServiceList()
{

	Order* temp = nullptr;
	

	if (VIP_Orders.dequeue(temp)) {
			ServicingList.enqueue(temp);
			temp->setStatus(SRV);
			NumWaitingOrders[TYPE_VIP]-- ;
	}
		 
	if (VGAN_Orders.dequeue(temp)) {
			ServicingList.enqueue(temp);
			temp->setStatus(SRV);
			NumWaitingOrders[TYPE_VGAN]--;
	}
		
	if (NRM_Orders.dequeue(temp)) {
			ServicingList.enqueue(temp);
			temp->setStatus(SRV);
			NumWaitingOrders[TYPE_NRM]--;
	}
	

}

void Restaurant::MoveServicedOrdersToFinishedList()
{
	static int ServiceCounter = 0;
	ServiceCounter++;

	if (ServiceCounter == 5) {
		ServiceCounter = 0 ;
		bool VIPtaken = false;
		bool Normaltaken = false;
		bool Vegantaken = false;

		Order* temp;
		Queue<Order*> tempQ;
		while (!ServicingList.isEmpty() && (!VIPtaken || !Normaltaken || !Vegantaken ) ) {
				ServicingList.dequeue(temp);
				switch (temp->GetType()) {
					case TYPE_VIP :
									if (!VIPtaken) {
										Finished.enqueue(temp);
										VIPtaken = true;
										temp->setStatus(DONE);
									}
									else tempQ.enqueue(temp);
									break;
					case TYPE_NRM:
									if (!Normaltaken) {
										Finished.enqueue(temp);
										Normaltaken = true;
										temp->setStatus(DONE);
									}
									else tempQ.enqueue(temp);
									break;

					case TYPE_VGAN:
									if (!Vegantaken) {
										Finished.enqueue(temp);
										Vegantaken = true;
										temp->setStatus(DONE);
									}
									else tempQ.enqueue(temp);
									break;
				}
		}
		while (!ServicingList.isEmpty()) {
			ServicingList.dequeue(temp);
			tempQ.enqueue(temp);
		}
		while (!tempQ.isEmpty()) {
			tempQ.dequeue(temp);
			ServicingList.enqueue(temp);
		}
	}
}

Restaurant::Restaurant()
{
	//Initializing waiting orders counters
	for(int i = 0 ; i<TYPE_CNT ; i++) NumWaitingOrders[i] = 0 ;

	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;


	pGUI->PrintMessage("Please enter a path to the text file containing Cooks and Events (e.g: F:\\folder_name\\file_name)");
	string inputfile = pGUI->GetString();
	bool success = loadEventsAndCooksFromFile(inputfile + ".txt");
	while (!success) {
		pGUI->PrintMessage("Couldn't Open File ! Please enter another path");
		inputfile = pGUI->GetString();
		success = loadEventsAndCooksFromFile(inputfile + ".txt");
	}

	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Simulate();

	};

}
Restaurant::~Restaurant()
{
	if (pGUI)
		delete pGUI;
}

//////////////////////////////////  Event handling functions   /////////////////////////////

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event* pE;
	while (EventsQueue.peekFront(pE))	//as long as there are more events
	{
		if (pE->getEventTime() > CurrentTimeStep)	//no more events at current timestep
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

void Restaurant::FillDrawingList()
{
	//This function should be implemented in phase1
	//It should add ALL orders and Cooks to the drawing list
	//It should get orders from orders lists/queues/stacks/whatever (same for Cooks)
	//To add orders it should call function  void GUI::AddToDrawingList(Order* pOrd);
	//To add Cooks it should call function  void GUI::AddToDrawingList(Cook* pCc);

	Cook** CooksArr = Kitch.toArray();
	for (int i = 0; i < Kitch.getNumCooks(); ++i)
		pGUI->AddToDrawingList(CooksArr[i]);
	delete[] CooksArr;


	QueuePriority<Order*>* Waiting = SortWaitingOrdersByArrival();
	Order* temp;
	while (Waiting->dequeue(temp)) pGUI->AddToDrawingList(temp);
	delete Waiting;

	/*QueuePriority<Order*> InService ;
	int ServicedOrdersCount;
	Order** OrdersArr = ServicingList.toArray(ServicedOrdersCount);
	for (int i = 0; i < ServicedOrdersCount; i++) {
		InService.enqueue(OrdersArr[i], -OrdersArr[i]->getAssignmentTime());
	}
	delete[] OrdersArr;
	while (InService.dequeue(temp)) pGUI->AddToDrawingList(temp);*/

	Queue<Order*> tempServicing;
	while (ServicingList.dequeue(temp)) {
		pGUI->AddToDrawingList(temp);
		tempServicing.enqueue(temp);
	}
	while (tempServicing.dequeue(temp)) ServicingList.enqueue(temp);
	
	Queue<Order*> tempFinished;
	while (Finished.dequeue(temp)) {
		pGUI->AddToDrawingList(temp);
		tempFinished.enqueue(temp);
	}
	while(tempFinished.dequeue(temp)) Finished.enqueue(temp);


}

bool Restaurant::loadEventsAndCooksFromFile(string path)
{
	std::ifstream file;
	file.open(path);

	if (file.is_open()) {
		Kitch.loadCooksFromFile(file);
		file >> autoPlimit;
		loadEventsFromFile(file);

		file.close();
		return true;
	}
	else return false;
}

void Restaurant::loadEventsFromFile(std::ifstream& file)
{

	int num;
	file >> num;
	Event* temp;
	for (int i = 0; i < num; ++i)
	{
		char eventType;
		file >> eventType;
		temp = CreateSpecificEvent(eventType);
		temp->readInfo(file);
		EventsQueue.enqueue(temp);
	}

}

void Restaurant::Simulate()
{
	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		//std::cout << "Time Step :" << CurrentTimeStep << "\n";
		//std::cout << "Status of Events Queue :\n";
		//EventsQueue.print();

		//print current timestep, other information
		pGUI->PrintNumber(CurrentTimeStep);


		//execute all events at current time step
		ExecuteEvents(CurrentTimeStep);	

		//Moving from Waiting to In-Service
		MoveWaitingOrdersToServiceList();

		//Moving from In-Service to Finished IF POSSIBLE
		MoveServicedOrdersToFinishedList();
		
		//Increment Waiting Orders WaitTime and In-Service Orders ServTime
		UpdateOrderTimes();

		//Display Objects
		FillDrawingList();
		//std::cout << "Servcing List:\n";
		//ServicingList.print();
		//std::cout << "Finished List:\n";
		//Finished.print();

		pGUI->UpdateInterface();
		PrintWaitingOrdersInformation();
		PrintAvilableCooksInformation();

		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
		pGUI->waitForClick();
		//std::cout << "Orders List:\n";
		//std::cout << "    Normals:\n";
		//NRM_Orders.print();
		//std::cout << "\n    Vegans:\n";
		//VGAN_Orders.print();		
		//std::cout << "\n    VIPs:\n";
		//VIP_Orders.print();
	}

	//std::cout << "The Events Queue Is now EMPTY !!! \n\n\n\n\n\n\n\n\n\n\n\n";
	while ( !ServicingList.isEmpty()   ) {
		//std::cout << "Time Step :" << CurrentTimeStep << "\n";
		pGUI->PrintNumber(CurrentTimeStep);


		//Main Logic
		MoveWaitingOrdersToServiceList();

		MoveServicedOrdersToFinishedList();

		UpdateOrderTimes();

		//Display
		FillDrawingList();
		//std::cout << "Servcing List:\n";
		//ServicingList.print();
		//std::cout << "Finished List:\n";
		//Finished.print();
		pGUI->UpdateInterface();
		PrintWaitingOrdersInformation();
		PrintAvilableCooksInformation();

		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
		pGUI->ResetDrawingList();
		pGUI->waitForClick();
	}
}

void Restaurant::PrintWaitingOrdersInformation()
{
	string waitingOrdersInformation("Waiting Orders : Normal->");
	char number[10];
	itoa(NumWaitingOrders[TYPE_NRM], number, 10);
	waitingOrdersInformation += number;
	waitingOrdersInformation += ", Vegan->";
	itoa(NumWaitingOrders[TYPE_VGAN], number, 10);
	waitingOrdersInformation += number;
	waitingOrdersInformation += ", VIP->";
	itoa(NumWaitingOrders[TYPE_VIP], number, 10);
	waitingOrdersInformation += number;
	pGUI->PrintMessage(waitingOrdersInformation, 1);
}

void Restaurant::PrintAvilableCooksInformation()
{
	string availableCooksInformation("Avilable Cooks : Normal->");
	char number[10];
	itoa(Kitch.getActiveNormalCooks(), number, 10);
	availableCooksInformation += number ;
 
	availableCooksInformation += ", Vegan->";
	itoa(Kitch.getActiveVeganCooks(), number, 10);
	availableCooksInformation += number;
 
	availableCooksInformation += ", VIP->";
	itoa(Kitch.getActiveVIPCooks(), number, 10);
	availableCooksInformation += number;

	pGUI->PrintMessage(availableCooksInformation, 2);
}


void Restaurant::AddtoVIP_Queue(Order* pOrd)
{
	 VIP_Orders.enqueue(pOrd, CaclulateVIPPriorty(pOrd) );
	 // std::cout << "\nVIP Order number  " << pOrd->GetID() << "   has priorty" << CaclulateVIPPriorty(pOrd)<<"\n";
	 NumWaitingOrders[TYPE_VIP]++;
}
void Restaurant::AddtoNormal_Queue(Order* pOrd)
{
		NRM_Orders.enqueue(pOrd);
		NumWaitingOrders[TYPE_NRM]++;
}
void Restaurant::AddtoVegan_Queue(Order* pOrd)
{
		VGAN_Orders.enqueue(pOrd);
		NumWaitingOrders[TYPE_VGAN]++;
}
void Restaurant::RemoveFromNormalQueue(int id)
{
	Order* tempOrder;
	Queue<Order*> tempQ;
	while (!NRM_Orders.isEmpty())  //To remove order from Normal Order list
	{
		NRM_Orders.dequeue(tempOrder);

		if (tempOrder->GetID() == id) 
		{
			NumWaitingOrders[TYPE_NRM]--;
			delete tempOrder; 
			continue;
		}


		tempQ.enqueue(tempOrder);
	}

	while (!tempQ.isEmpty())
	{
		tempQ.dequeue(tempOrder);
		NRM_Orders.enqueue(tempOrder);
	}

}
