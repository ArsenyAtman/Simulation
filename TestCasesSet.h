#ifndef TEST_CASES_SET_H
#define TEST_CASES_SET_H

#include "TestCases.h"
#include "VectorTestCases.h"
#include "PointersTestCases.h"

namespace TestsCasesSet
{
    using namespace TestCases;
    using testCase = void(*)();

    constexpr testCase testCases[] = {  checkPow,
                                        checkSign,
                                        checkAbs,
                                        checkMin,
                                        checkSqrt,
                                        checkVectorAdd,
                                        checkVectorSub,
                                        checkVectorScale,
                                        checkVectorNull,
                                        checkVectorNormalize,
                                        checkVectorLength,
                                        checkVectorLengthSquared,
                                        checkUniquePointer
                                        };

    constexpr int size = sizeof(testCases) / sizeof(testCase);
}

#endif
