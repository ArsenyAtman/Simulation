#ifndef TEST_CASES_H
#define TEST_CASES_H

#include "Check.h"

#include "Math.h"

namespace TestCases
{
    void checkPow()
    {
        check("Pow default int", Math::pow(5, 2) == 25);
        check("Pow one int", Math::pow(1, 2) == 1);
        check("Pow zero int", Math::pow(0, 2) == 0);
        check("Pow signed int", Math::pow(-2, 2) == 4);
        check("Pow int of 1", Math::pow(6, 1) == 6);
        check("Pow int of 0", Math::pow(6, 0) == 1);

        check("Pow default float", Math::pow(5.0f, 2) == 25.0f);
        check("Pow one float", Math::pow(1.0f, 2) == 1.0f);
        check("Pow zero float", Math::pow(0.0f, 2) == 0.0f);
        check("Pow signed float", Math::pow(-2.0f) == 4.0f);
        check("Pow float of 1", Math::pow(6.3f, 1) == 6.3f);
        check("Pow float of 0", Math::pow(6.3f, 0) == 1.0f);
    }

    void checkSign()
    {
        check("Sign of negative int", Math::sign(-12343) == -1);
        check("Sign of positive int", Math::sign(89235) == 1);
        check("Sign of zero int", Math::sign(0) == 1);

        check("Sign of negative", Math::sign(-12343.92345f) == -1.0f);
        check("Sign of positive", Math::sign(89235.92345f) == 1.0f);
        check("Sign of zero", Math::sign(0.0f) == 1.0f);
    }

    void checkAbs()
    {
        check("Abs of negative int", Math::abs(-12343) == 12343);
        check("Abs of positive int", Math::abs(89235) == 89235);
        check("Abs of zero int", Math::abs(0) == 0);

        check("Sign of negative float", Math::sign(-12343.92345f) == -1.0f);
        check("Sign of positive float", Math::sign(89235.92345f) == 1.0f);
        check("Sign of zero float", Math::sign(0.0f) == 1.0f);
    }

    void checkMin()
    {
        check("Min int >", Math::min(12, -45) == -45);
        check("Min int <", Math::min(5, 63) == 5);
        check("Min int =", Math::min(9, 9) == 9);

        check("Min float >", Math::min(12.45f, 12.449f) == 12.449f);
        check("Min float <", Math::min(-324.67f, 265.878f) == -324.67f);
        check("Min float =", Math::min(0.0f, 0.0f) == 0.0f);
    }

    void checkSqrt()
    {
        {
            int val = 3;
            check("Sqrt int", val == Math::sqrt(val * val));
        }

        {
            float val = 3.0f;
            check("Sqrt float", val == Math::sqrt(val * val));
        }

        {
            float val = -10.0f;
            check("Sqrt float negative", Math::abs(val) == Math::sqrt(val * val));
        }
    }
}

#endif
