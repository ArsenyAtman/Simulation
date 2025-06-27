#ifndef POINTERS_TEST_CASES_H
#define POINTERS_TEST_CASES_H

#include "Check.h"

#include "UniquePointer.h"
#include "ObservingPointer.h"
#include "SharedPointer.h"
#include "WeakPointer.h"

namespace TestCases
{
    struct Resource
    {
        int& counterRef;

        Resource(int& counter) :
            counterRef(counter)
        {
            ++counterRef;
        }

        ~Resource()
        {
            --counterRef;
        }
    };

    void checkUniquePointer()
    {
        int counter = 0;
        {
            UniquePointer<Resource> ptr(new Resource(counter));
            check("UniquePointer: Count of instances inside the scope", ptr->counterRef, 1);
        }
        check("UniquePointer: Count of instances outside the scope", counter, 0);
    }

    void checkObservingPointer()
    {
        int counter = 0;
        {
            UniquePointer<Resource> ptr(new Resource(counter));
            {
                ObservingPointer<Resource> ptr2(ptr);
                check("ObservingPointer: Count of instances inside the scope", ptr->counterRef, 1);
            }
            check("ObservingPointer: Count of instances outside the scope", counter, 1);
        }
        check("ObservingPointer: Count of instances in the outermost scope", counter, 0);
    }

    void checkSharedPointer()
    {
        int counter = 0;
        {
            SharedPointer<Resource> ptr(new Resource(counter));
            {
                SharedPointer<Resource> ptr2(ptr);
                check("SharedPointer: Count of instances inside the scope", ptr->counterRef, 1);
            }
            check("SharedPointer: Count of instances outside the scope", counter, 1);
        }
        check("SharedPointer: Count of instances in the outermost scope", counter, 0);
    }

    void checkWeakPointer()
    {
        int counter = 0;
        {
            SharedPointer<Resource> ptr(new Resource(counter));
            {
                WeakPointer<Resource> ptr2(ptr);
                check("WeakPointer: Count of instances inside the scope", ptr->counterRef, 1);
            }
            check("WeakPointer: Count of instances outside the scope", counter, 1);
        }
        check("WeakPointer: Count of instances in the outermost scope", counter, 0);
    }
}

#endif
