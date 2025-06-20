#ifndef TESTS_H
#define TESTS

#include "TestCasesSet.h"
#include "Check.h"

#include <iostream>

namespace Tests
{
    void runTests()
    {
        TestStats::resetStats();

        std::cout << "Running tests:" << std::endl;

        constexpr int countOfCases = TestsCasesSet::size;
        for (int i = 0; i < countOfCases; ++i)
        {
            TestsCasesSet::testCases[i]();
        }

        std::cout << "Finished. " << TestStats::failedChecks << "/" << TestStats::passedChecks + TestStats::failedChecks << " failed." << std::endl;
        std::cout << std::endl;
    }
}

#endif
