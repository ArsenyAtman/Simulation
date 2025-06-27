#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

#include "ReferenceCounter.h"

template <typename T>
class UniquePointer
{

public:

    explicit UniquePointer(T* managedResource);
    UniquePointer(UniquePointer<T>&& other);
    UniquePointer<T>& operator = (UniquePointer<T>&& other);

    // Forbid copying
    UniquePointer(const UniquePointer<T>& other) = delete;
    UniquePointer<T>& operator = (const UniquePointer<T>& other) = delete;

    ~UniquePointer();
    
    ReferenceCounter* getReferenceCounter() const { return referenceCounter; }

    const T* get() const { return resource; }
    T* get() { return resource; }

    T* operator -> () { return this->get(); }
    const T* operator -> () const { return this->get(); }

private:

    void cleanUpResource();

    ReferenceCounter* referenceCounter;
    T* resource;
};

template<typename T>
UniquePointer<T>::UniquePointer(T* managedResource) :
    resource(managedResource),
    referenceCounter(new ReferenceCounter())
{
    // ...
}

template<typename T>
UniquePointer<T>::UniquePointer(UniquePointer<T>&& other) :
    resource(other.resource),
    referenceCounter(other.referenceCounter)
{
    referenceCounter->addStrongReference();

    other.resource = nullptr;
}

template<typename T>
UniquePointer<T>& UniquePointer<T>::operator = (UniquePointer<T>&& other)
{
    if (this == &other)
    {
        return *this;
    }

    cleanUpResource();

    resource = other.resource;
    referenceCounter = other.referenceCounter();
    referenceCounter->addStrongReference();

    other.resource = nullptr;

}

template<typename T>
UniquePointer<T>::~UniquePointer()
{
    cleanUpResource();
}

template<typename T>
void UniquePointer<T>::cleanUpResource()
{
	referenceCounter->removeSharedReference();
	if (referenceCounter->isValidCounter() == false)
	{
		delete referenceCounter;
	}

	delete resource;
}

#endif
