#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINER_H

template <typename T>
class UniquePointer
{

public:

    T* const resource;

    UniquePointer(T* managedResource) :
        resource(managedResource)
    {
        // ...
    }

    ~UniquePointer()
    {
        //delete resource;
    }
};

#endif
