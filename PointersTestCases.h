#ifndef POINTERS_TEST_CASES_H
#define POINTERS_TEST_CASES_H

#include "Check.h"

#include "UniquePointer.h"

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
            UniquePointer<Resource> ptr = new Resource(counter);
            check("Count of instences after allocation", counter > 0);
        }
        check("Count of instances after destruction", counter, 0);
    }
}

#endif
