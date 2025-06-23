#ifndef CHECK_H
#define CHECK_H

#include <iostream>

namespace TestStats
{
    static int passedChecks = 0;
    static int failedChecks = 0;

    void resetStats()
    {
        passedChecks = 0;
        failedChecks = 0;
    }
}

namespace TestCases
{
    void check(const char* name, bool value)
    {
        if (value)
        {
            std::cout << "[+]";
        }
        else
        {
            std::cout << "[-]";
        }

        std::cout << "\"" << name << "\" - ";

        if (value)
        {
            std::cout << "passed.";
            ++TestStats::passedChecks;
        }
        else
        {
            std:: cout << "failed.";
            ++TestStats::failedChecks;
        }
        std::cout << std::endl;
    }

    template <typename T>
    void check(const char* name, T actualValue, T expectedValue)
    {
        bool checkResult = (actualValue == expectedValue);

        if (checkResult)
        {
            std::cout << "[+]";
        }
        else
        {
            std::cout << "[-]";
        }

        std::cout << "\"" << name << "\" - ";

        if (checkResult)
        {
            std::cout << "passed.";
            ++TestStats::passedChecks;
        }
        else
        {
            std:: cout << "failed. Expected " << expectedValue << " , but actual was " << actualValue << ".";
            ++TestStats::failedChecks;
        }
        std::cout << std::endl;
    }
}

#endif
