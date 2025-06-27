#ifndef OBSERVING_POINTER_H
#define OBSERVING_POINTER_H

#include "UniquePointer.h"
#include "ReferenceCounter.h"

template<typename T>
class ObservingPointer
{

public:

	ObservingPointer(UniquePointer<T>& uniquePointer);
	ObservingPointer(const ObservingPointer<T>& other);
	ObservingPointer(const ObservingPointer<T>&& other);

	ObservingPointer<T>& operator = (const ObservingPointer<T>& other);
	ObservingPointer<T>& operator = (const ObservingPointer<T>&& other);

	~ObservingPointer();

	bool isValid() const { return referenceCounter->isValidResource(); }

	T* get() { return isValid() ? resource : nullptr; }
	const T* get() const { return isValid() ? resource : nullptr; }

	T* operator -> () { return this->get(); }
	const T* operator -> () const { return this->get(); }

private:

	void unreferenceResource();

	ReferenceCounter* referenceCounter;
	T* resource;
};

template<typename T>
ObservingPointer<T>::ObservingPointer(UniquePointer<T>& uniquePointer) :
	resource(uniquePointer.get()),
	referenceCounter(uniquePointer.getReferenceCounter())
{
	referenceCounter->addWeakReference();
}

template<typename T>
ObservingPointer<T>::ObservingPointer(const ObservingPointer<T>& other) : // copy constructor
	resource(other.resource),
	referenceCounter(other.referenceCounter)
{
	referenceCounter->addWeakReference();
}

template<typename T>
ObservingPointer<T>::ObservingPointer(const ObservingPointer<T>&& other) : // move constructor
	resource(other.resource),
	referenceCounter(other.referenceCounter)
{
	referenceCounter->addWeakReference();
}

template<typename T>
ObservingPointer<T>& ObservingPointer<T>::operator = (const ObservingPointer<T>& other) // copy operator
{
	if (this == &other)
	{
		return *this;
	}

	unreferenceResource();

	resource = other.resource;
	referenceCounter = other.referenceCounter;
	referenceCounter->addWeakReference();

	return *this;
}

template<typename T>
ObservingPointer<T>& ObservingPointer<T>::operator = (const ObservingPointer<T>&& other) // move operator
{
	if (this == &other)
	{
		return *this;
	}

	unreferenceResource();

	resource = other.resource;
	referenceCounter = other.referenceCounter;
	referenceCounter->addWeakReference();

	return *this;
}

template<typename T>
ObservingPointer<T>::~ObservingPointer()
{
	unreferenceResource();
}

template<typename T>
void ObservingPointer<T>::unreferenceResource()
{
	referenceCounter->removeWeakReference();
	if (referenceCounter->isValidCounter() == false)
	{
		delete referenceCounter;
	}
}

#endif
