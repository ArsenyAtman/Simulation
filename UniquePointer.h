#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

#include "ReferenceCounter.h"

template <typename T>
class UniquePointer
{

public:

    explicit UniquePointer(T* managedResource) :
        resource(managedResource),
        referenceCounter(new ReferenceCounter())
    {
        // ...
    }

    ~UniquePointer()
    {
        cleanUpResource();
    }

    // Forbid copying
    UniquePointer(const UniquePointer<T>& other) = delete;
    UniquePointer& operator = (const UniquePointer<T>& other) = delete;

    UniquePointer(UniquePointer<T>&& other) :
        resource(other.resource),
        referenceCounter(other.referenceCounter)
    {
        referenceCounter->addSharedReference();

        other.resource = nullptr;
    }

    UniquePointer& operator = (UniquePointer<T>&& other)
    {
        if (this == &other)
        {
            return *this;
        }

        cleanUpResource();

        resource = other.resource;
        referenceCounter = other.referenceCounter();
        referenceCounter->addSharedReference();

        other.resource = nullptr;

    }
    
    ReferenceCounter* getReferenceCounter() const { return referenceCounter; }

    const T* get() const { return resource; }
    T* get() { return resource; }

    T* operator -> () { return this->get(); }
    const T* operator -> () const { return this->get(); }

private:

    void cleanUpResource()
    {
        referenceCounter->removeSharedReference();
        if (referenceCounter->isValidCounter() == false)
        {
            delete referenceCounter;
        }

        delete resource;
    }

    ReferenceCounter* referenceCounter;
    T* resource;
};

#endif
