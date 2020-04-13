#pragma once


template <typename T>
class DynamicBag
{
	T* firstElement;
	int size, capacity;
	const int defaultInitialCapacity = 10;
	void DeleteElement(int index);

public:
	DynamicBag();
	DynamicBag(T arr[], int size);

	void initializeCapacity(int);
	int getSize();

	T	 take();
	void addElement(T elem);
	bool RemoveElement(T elem);

	~DynamicBag();

};

template<typename T>
DynamicBag<T>::DynamicBag()
{
	firstElement = NULL;
	size = 0;
	capacity = 0;
}

template<typename T>
DynamicBag<T>::DynamicBag(T arr[], int size)
{
	if (size <= 0) {
		firstElement = NULL;
		this->size = 0;
		capacity = 0;
	}
	else {
		this->size = size;
		capacity = size;
		firstElement = new T[capacity];
		for (int i = 0; i < size; ++i) {
			firstElement[i] = arr[i];
		}
	}
}

template<typename T>
inline void DynamicBag<T>::initializeCapacity(int s)
{
	if (!firstElement && s > 0) {
		firstElement = new T[s];
		capacity = s;
	}
}

template<typename T>
inline int DynamicBag<T>::getSize()
{
	return size;
}

template<typename T>
inline T DynamicBag<T>::take()
{
	static int index = 0;

	if (index < size - 1) {
		index++;
		return firstElement[index - 1];
	}
	else {
		index = 0;
		return firstElement[size - 1];
	}
}

template<typename T>
inline void DynamicBag<T>::addElement(T elem)
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
bool  DynamicBag<T>::RemoveElement(T elem)
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
inline void DynamicBag<T>::DeleteElement(int index)
{
	if (!(size > 0 && index >= 0 && index < size)) return;

	if (size - 1 < capacity / 2) {
		capacity = capacity / 2;
		T* NewfirstElement = new T[capacity];
		for (int i = 0; i < size; ++i) {
			NewfirstElement[i] = firstElement[i];
		}
		delete[] firstElement;
		firstElement = NewfirstElement;
	}

	firstElement[index] = firstElement[size - 1];
	size--;

}

template<typename T>
DynamicBag<T>::~DynamicBag()
{
	delete[] firstElement;
}