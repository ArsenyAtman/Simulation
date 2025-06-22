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

    // Forbid copying
    UniquePointer(const UniquePointer<T>& other) = delete;

    ~UniquePointer()
    {
        referenceCounter->removeSharedReference();
        if (referenceCounter->isValidCounter() == false)
        {
            delete referenceCounter;
        }

        delete resource;
    }
    
    ReferenceCounter* getReferenceCounter() const { return referenceCounter; }
    T* get() const { return resource; }

private:

    ReferenceCounter* referenceCounter;
    T* resource;
};

#endif
