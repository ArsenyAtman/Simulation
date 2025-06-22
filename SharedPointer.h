#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include "ReferenceCounter.h"
#include "Size.h"

template<typename T>
class SharedPointer
{

public:

	explicit SharedPointer(T* managedResource) :
		resource(managedResource),
		referenceCounter(new ReferenceCounter())
	{
		// ...
	}

	SharedPointer(const SharedPointer<T>& other) :
		resource(other.resource),
		referenceCounter(other.referenceCounter)
	{
		referenceCounter->addSharedReference();
	}

	~SharedPointer()
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

	ReferenceCounter* getReferenceCounter() const { return referenceCounter; }
	T* get() const { return resource; }

	// TODO: copy operator

private:

	ReferenceCounter* referenceCounter;
	T* resource;
};

#endif
