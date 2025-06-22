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

	WeakPointer(const WeakPointer<T>& weakPointer) :
		resource(weakPointer.get()),
		referenceCounter(weakPointer.getReferenceCounter())
	{
		referenceCounter->addWeakReference();
	}

	~WeakPointer()
	{
		referenceCounter->removeWeakReference();
		if (referenceCounter->isValidCounter() == false)
		{
			delete referenceCounter;
		}
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

	ReferenceCounter* referenceCounter;
	T* resource;
};

#endif
