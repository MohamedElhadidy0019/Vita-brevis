
#ifndef __PNODE_H_
#define __PNODE_H_
#include<iostream>
using namespace std;
template < typename T>
class NodePriority
{
private:
	T item; // A data item
	NodePriority<T>* next; // Pointer to next node
	int priority;
public:
	NodePriority();
	NodePriority(const T& r_Item,int);	//passing by const ref.
	NodePriority(const T& r_Item, NodePriority<T>* nextNodePtr,int);
	void setItem(const T& r_Item);
	void setNext(NodePriority<T>* nextNodePtr);
	void setPriority(int);
	int  getPriority();
	T getItem() const;
	NodePriority<T>* getNext() const;
}; // end NodePriority


template < typename T>
NodePriority<T>::NodePriority()
{
	next = nullptr;
	priority = 0;
}

template < typename T>
NodePriority<T>::NodePriority(const T& r_Item,int x)
{
	priority = x;
	item = r_Item;
	next = nullptr;
}

template < typename T>
NodePriority<T>::NodePriority(const T& r_Item, NodePriority<T>* nextNodePtr,int x)
{
	item = r_Item;
	next = nextNodePtr;
	priority = x;
}
template < typename T>
void NodePriority<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void NodePriority<T>::setNext(NodePriority<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template<typename T>
inline void NodePriority<T>::setPriority(int x)
{
	priority = x;
}

template<typename T>
inline int NodePriority<T>::getPriority()
{
	return priority;
}

template < typename T>
T NodePriority<T>::getItem() const
{
	return item;
}

template < typename T>
NodePriority<T>* NodePriority<T>::getNext() const
{
	return next;
}

#endif