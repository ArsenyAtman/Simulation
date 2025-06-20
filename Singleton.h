#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{

public:

    static void init(T* resourceToManage)
    {
        if(resource == nullptr)
        {
            resource = resourceToManage;
        }
    }

    static T& get() { return *resource; }

private:

    static inline T* resource = nullptr; // inline to allow init with the definition

    Singleton() = default;

    ~Singletone()
    {
        if (resource != nullptr)
        {
            delete resource;
        }
    }

}

#endif
