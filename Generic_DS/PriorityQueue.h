#ifndef __PQUEUE_H_
#define __PQUEUE_H_

/*This code is an updated version from "Data Abstraction & Problem Solving with C++,WALLS AND MIRRORS ,SIXTH EDITION"*/

/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

				The NodePriority: item of type T and a "next" pointer
					-------------
					| item| next | --->
					-------------
General QueuePriority case:

				 frontPtr																backPtr
					\											   						/
					 \											  					   /
					------------- 	  ------------- 	  ------------- 	  -------------
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

				 frontptr	 backptr
						\	 /
						 \	/
					---- NULL ------


Single NodePriority Case:
				 frontPtr	 backPtr
					\		/
					 \	   /
					--------
					|	|nxt -->NULL
					--------

*/

#include "NodePriority.h"

template <typename T>
class QueuePriority
{
private:

	NodePriority<T>* backPtr;
	NodePriority<T>* frontPtr;
public:
	QueuePriority();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool enqueue(T, int);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	T* toArray(int& count);	//returns array of T (array if items)
	void plugNode(NodePriority<T>*, T,int);
	void print();
	~QueuePriority();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: QueuePriority()
The constructor of the QueuePriority class.

*/

template <typename T>
QueuePriority<T>::QueuePriority()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool QueuePriority<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool QueuePriority<T>::enqueue(const T& newEntry)
{
	NodePriority<T>* newNodePtr = new NodePriority<T>(newEntry,0);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	return true;
} // end enqueue

template<typename T>
inline bool QueuePriority<T>::enqueue(T newEntry, int priority)
{
	NodePriority<T>* addedNode = new NodePriority<T>(newEntry, priority);
	if (isEmpty())
	{
		frontPtr = addedNode; // The queue is empty
		return true;
	}
		
	if (addedNode->getPriority() > frontPtr->getPriority())
	{
		addedNode->setNext(frontPtr);
		frontPtr = addedNode;
		return true;
	}
	NodePriority<T>* before = frontPtr;
	NodePriority<T>* iterator = frontPtr->getNext();
	while (iterator)
	{
		if (iterator->getPriority() < priority)
		{
			before->setNext(addedNode);
			addedNode->setNext(iterator);
			return true;
		}
		before = iterator;
		iterator = iterator->getNext();
	}
	before->setNext(addedNode);
	addedNode->setNext(NULL);
	backPtr = addedNode;
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. 

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool QueuePriority<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	NodePriority<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// QueuePriority is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if QueuePriority is empty
*/
template <typename T>
bool QueuePriority<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
QueuePriority<T>::~QueuePriority()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if QueuePriority is empty)
returns: The array of T. (nullptr if QueuePriority is empty)
*/

template <typename T>
T* QueuePriority<T>::toArray(int& count)
{
	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the QueuePriority
	NodePriority<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

template<typename T>
inline void QueuePriority<T>::plugNode(NodePriority<T>*firstNode, T thedata,int pri)
{
	NodePriority<T>* newptr = new NodePriority<T>;
	newptr->setItem(thedata);
	newptr->setPriority(pri);
	newptr->setNext(firstNode->getNext());
	firstNode->setNext(newptr);
}


//Just for Debugging
template<typename T>
inline void QueuePriority<T>::print()
{
	NodePriority<T>* iterator = this->frontPtr;
	while (iterator)
	{
		iterator->getItem()->print() ;
		cout << "\n";
		iterator = iterator->getNext();
	}
	cout << "END OF QUEUE\n";
}

#endif
