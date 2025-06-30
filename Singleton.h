#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton
{

public:

    static T& get()
    {
        if (resource == nullptr)
        {
            resource = new T();
        }

        return *resource;
    }

    virtual ~Singleton()
    {
        delete resource;
    }

protected:

    Singleton() = default;

private:

    static inline T* resource = nullptr; // inline to allow init with the definition
};

#endif
