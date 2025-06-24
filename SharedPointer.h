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

	// TODO: Convert from weak ptr to shared pointer, but prevent the coversion in case where the weak pointer leads to a resource managed by unique pointer

	~SharedPointer()
	{
		unreferenceResource();
	}

	SharedPointer(const SharedPointer<T>& other) : // copy constructor
		resource(other.resource),
		referenceCounter(other.referenceCounter)
	{
		referenceCounter->addSharedReference();
	}

	SharedPointer& operator = (const SharedPointer<T>& other) // copy operator
	{
		if (this == &other)
		{
			return *this;
		}

		unreferenceResource();

		resource = other.resource;
		referenceCounter = other.referenceCounter;
		referenceCounter->addSharedReference();

		return *this;
	}

	SharedPointer(const SharedPointer<T>&& other) : // move constructor
		resource(other.resource),
		referenceCounter(other.referenceCounter)
	{
		referenceCounter->addSharedReference();
	}

	SharedPointer& operator = (const SharedPointer<T>&& other) // move operator
	{
		if (this == &other)
		{
			return *this;
		}

		unreferenceResource();

		resource = other.resource;
		referenceCounter = other.referenceCounter;
		referenceCounter->addSharedReference();

		return *this;
	}

	ReferenceCounter* getReferenceCounter() const { return referenceCounter; }

	T* get() { return resource; }
	const T* get() const { return resource; }

	T* operator -> () { return this->get(); }
	const T* operator -> () const { return this->get(); }

private:

	void unreferenceResource()
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

	ReferenceCounter* referenceCounter;
	T* resource;
};

#endif
