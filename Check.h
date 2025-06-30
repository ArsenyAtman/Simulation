#ifndef CHECK_H
#define CHECK_H

#include "Singleton.h"
#include "Console.h"

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
    void check(const String& name, bool value)
    {
        if (value)
        {
            Console::print("[ ]");
        }
        else
        {
            Console::print("[X]");
        }

        Console::print("\"" + name + "\" - ");

        if (value)
        {
            Console::print("passed.");
            ++TestStats::passedChecks;
        }
        else
        {
            Console::print("failed.");
            ++TestStats::failedChecks;
        }
        Console::println();
    }

    template <typename T>
    void check(const String& name, T actualValue, T expectedValue)
    {
        bool checkResult = (actualValue == expectedValue);

        if (checkResult)
        {
            Console::print("[ ]");
        }
        else
        {
            Console::print("[X]");
        }

        Console::print("\"" + name + "\" - ");

        if (checkResult)
        {
            Console::print("passed.");
            ++TestStats::passedChecks;
        }
        else
        {
            Singleton<Console>::get().print("failed. Expected " + String(expectedValue) + " , but actual was " + String(actualValue) + ".");
            ++TestStats::failedChecks;
        }
        Singleton<Console>::get().println();
    }
}

#endif
