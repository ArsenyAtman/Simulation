#ifndef WEAK_POINTER_H
#define WEAK_POINTER_H

#include "SharedPointer.h"
#include "UniquePointer.h"
#include "ReferenceCounter.h"

template<typename T>
class WeakPointer
{

public:

	WeakPointer(const SharedPointer<T>& sharedPointer) :
		resource(sharedPointer.get()),
		referenceCounter(sharedPointer.getReferenceCounter())
	{
		referenceCounter->addWeakReference();
	}

	WeakPointer(const UniquePointer<T>& uniquePointer) :
		resource(uniquePointer.get()),
		referenceCounter(uniquePointer.getReferenceCounter())
	{
		referenceCounter->addWeakReference();
	}

	~WeakPointer()
	{
		unreferenceResource();
	}

	WeakPointer(const WeakPointer<T>& other) : // copy constructor
		resource(other.resource),
		referenceCounter(other.referenceCounter)
	{
		referenceCounter->addWeakReference();
	}

	WeakPointer(const WeakPointer<T>&& other) : // move constructor
		resource(other.resource),
		referenceCounter(other.referenceCounter)
	{
		referenceCounter->addWeakReference();
	}

	WeakPointer& operator = (const WeakPointer<T>& other) // copy operator
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

	WeakPointer& operator = (const WeakPointer<T>&& other) // move operator
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

	bool isValid() const
	{
		return referenceCounter->isValidResource();
	}

	T* get() const
	{
		if (referenceCounter->isValidCounter())
		{
			return resource;
		}

		return nullptr;
	}
	
	// TODO: copy operator

private:

	void unreferenceResource()
	{
		referenceCounter->removeWeakReference();
		if (referenceCounter->isValidCounter() == false)
		{
			delete referenceCounter;
		}
	}

	ReferenceCounter* referenceCounter;
	T* resource;
};

#endif
