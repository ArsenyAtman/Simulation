#ifndef WEAK_POINTER_H
#define WEAK_POINTER_H

#include "ReferenceCounter.h"

template<typename T>
class SharedPointer;

template<typename T>
class WeakPointer
{

public:

	WeakPointer(SharedPointer<T>& sharedPointer);
	WeakPointer(const WeakPointer<T>& other) noexcept;
	WeakPointer(const WeakPointer<T>&& other) noexcept;

	WeakPointer<T>& operator = (const WeakPointer<T>& other) noexcept;
	WeakPointer<T>& operator = (const WeakPointer<T>&& other) noexcept;

	~WeakPointer();

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

#include "SharedPointer.h"

template<typename T>
WeakPointer<T>::WeakPointer(SharedPointer<T>& sharedPointer) :
	resource(sharedPointer.get()),
	referenceCounter(sharedPointer.getReferenceCounter())
{
	referenceCounter->addWeakReference();
}

template<typename T>
WeakPointer<T>::WeakPointer(const WeakPointer<T>& other) noexcept : // copy constructor
	resource(other.resource),
	referenceCounter(other.referenceCounter)
{
	referenceCounter->addWeakReference();
}

template<typename T>
WeakPointer<T>::WeakPointer(const WeakPointer<T>&& other) noexcept : // move constructor
	resource(other.resource),
	referenceCounter(other.referenceCounter)
{
	referenceCounter->addWeakReference();
}

template<typename T>
WeakPointer<T>& WeakPointer<T>::operator = (const WeakPointer<T>& other) noexcept // copy operator
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
WeakPointer<T>& WeakPointer<T>::operator = (const WeakPointer<T>&& other) noexcept // move operator
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
WeakPointer<T>::~WeakPointer()
{
	unreferenceResource();
}

template<typename T>
void WeakPointer<T>::unreferenceResource()
{
	referenceCounter->removeWeakReference();
	if (referenceCounter->isValidCounter() == false)
	{
		delete referenceCounter;
	}
}

#endif
