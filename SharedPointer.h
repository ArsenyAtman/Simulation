#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include "ReferenceCounter.h"
#include "Size.h"

template<typename T>
class WeakPointer;

template<typename T>
class SharedPointer
{

public:

	explicit SharedPointer(T* managedResource);
	SharedPointer(WeakPointer<T>& weakPointer);
	SharedPointer(const SharedPointer<T>& other);
	SharedPointer(const SharedPointer<T>&& other);

	SharedPointer<T>& operator = (const SharedPointer<T>& other);
	SharedPointer<T>& operator = (const SharedPointer<T>&& other);

	~SharedPointer();

	ReferenceCounter* getReferenceCounter() const { return referenceCounter; }

	T* get() { return resource; }
	const T* get() const { return resource; }

	T* operator -> () { return this->get(); }
	const T* operator -> () const { return this->get(); }

private:

	void unreferenceResource();

	ReferenceCounter* referenceCounter;
	T* resource;
};

#include "WeakPointer.h"

template<typename T>
SharedPointer<T>::SharedPointer(T* managedResource) :
	resource(managedResource),
	referenceCounter(new ReferenceCounter())
{
	// ...
}

template<typename T>
SharedPointer<T>::SharedPointer(WeakPointer<T>& weakPointer):
	resource(weakPointer.get()),
	referenceCounter(weakPointer.getReferenceCounter())
{
	referenceCounter->addStrongReference();
}

template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& other) : // copy constructor
	resource(other.resource),
	referenceCounter(other.referenceCounter)
{
	referenceCounter->addStrongReference();
}

template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>&& other) : // move constructor
	resource(other.resource),
	referenceCounter(other.referenceCounter)
{
	referenceCounter->addStrongReference();
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator = (const SharedPointer<T>& other) // copy operator
{
	if (this == &other)
	{
		return *this;
	}

	unreferenceResource();

	resource = other.resource;
	referenceCounter = other.referenceCounter;
	referenceCounter->addStrongReference();

	return *this;
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator = (const SharedPointer<T>&& other) // move operator
{
	if (this == &other)
	{
		return *this;
	}

	unreferenceResource();

	resource = other.resource;
	referenceCounter = other.referenceCounter;
	referenceCounter->addStrongReference();

	return *this;
}

template<typename T>
SharedPointer<T>::~SharedPointer()
{
	unreferenceResource();
}

template<typename T>
void SharedPointer<T>::unreferenceResource()
{
	referenceCounter->removeSharedReference();

	if (referenceCounter->isValidResource() == false)
	{
		delete resource;
	}

	if (referenceCounter->isValidCounter() == false)
	{
		delete referenceCounter;
	}
}

#endif
