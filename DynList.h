#pragma once

template <typename T>
class DynamicList {
	T* firstElement;
	int size;
	int capacity;
	const int defaultInitialCapacity = 10;
	void DeleteElement(int index);

public:
	DynamicList();
	DynamicList(T arr[], int size);

	void initializeCapacity(int);
	int getSize();

	void addElement(T elem);
	bool RemoveElement(T elem);

	~DynamicList();


};

template<typename T>
DynamicList<T>::DynamicList()
{
	firstElement = NULL;
	size = 0;
	capacity = 0;
}

template<typename T>
DynamicList<T>::DynamicList(T arr[], int size)
{
	if (size <= 0)
	{
		firstElement = NULL;
		this->size = 0;
		capacity = 0;
	}
	else
	{
		this->size = size;
		capacity = size;
		firstElement = new T[capacity];
		for (int i = 0; i < size; ++i) {
			firstElement[i] = arr[i];
		}
	}
}

template<typename T>
inline void DynamicList<T>::initializeCapacity(int s)
{
	if (!firstElement && s > 0) {
		firstElement = new T[s];
		capacity = s;
	}
}

template<typename T>
inline int DynamicList<T>::getSize()
{
	return size;
}

template<typename T>
inline void DynamicList<T>::addElement(T elem)
{
	if (size + 1 > capacity) {
		capacity = (capacity > 0) ?
			(2 * capacity) : defaultInitialCapacity;
		T* NewFirstElement = new T[capacity];

		for (int i = 0; i < size; ++i) {
			NewFirstElement[i] = firstElement[i];
		}
		if (size > 0) delete[] firstElement;
		NewFirstElement[size] = elem;

		firstElement = NewFirstElement;
		size++;
		return;
	}

	firstElement[size] = elem;
	size++;

}

template<typename T>
bool DynamicList<T>::RemoveElement(T elem)
{
	int i;
	for (i = 0; i < size; ++i) {
		if (firstElement[i] == elem) break;
	}
	int Size1 = size;
	DeleteElement(i);

	return (Size1 != size);
}

template<typename T>
inline void DynamicList<T>::DeleteElement(int index)
{
	if (!(size > 0 && index >= 0 && index < size)) return;

	if (size - 1 < capacity / 2) {
		capacity = capacity / 2;
		T* NewfirstElement = new T[capacity];
		for (int i = 0; i < index; ++i) {
			NewfirstElement[i] = firstElement[i];
		}
		for (int i = index + 1; i < size; ++i) {
			NewfirstElement[i - 1] = firstElement[i];
		}
		size--;
		delete[] firstElement;
		firstElement = NewfirstElement;
		return;
	}

	for (int i = index; i < size - 1; ++i)	firstElement[i] = firstElement[i + 1];
	size--;

}


template<typename T>
DynamicList<T>::~DynamicList()
{
	delete[] firstElement;
}
