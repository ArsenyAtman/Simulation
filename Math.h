#ifndef MATH_H
#define MATH_H

#include <cassert>

namespace Math
{
    constexpr float getPI() { return 3.14f; }

    template<typename T>
    constexpr T pow(T value, int exponent = 2)
    {
        if (exponent == 0)
        {
            return 1;
        }

        -- exponent;
        return value * Math::pow(value, exponent);
    }

    template<typename T>
    constexpr T sign(T value) { return value >= static_cast<T>(0) ? static_cast<T>(1) : static_cast<T>(- 1); }

    template<typename T>
    constexpr T abs(T value) { return value < static_cast<T>(0) ? -value : value; }

    template<typename T>
    constexpr T min(T value1, T value2) { return value1 < value2 ? value1 : value2; }

    template<typename T>
    constexpr T max(T value1, T value2) { return value1 > value2 ? value1 : value2; }

    template<typename T>
    constexpr T sqrt(T value, T precision = static_cast<T>(1e-6f))
    {
        // TODO: create own asserts and ensures
        assert(value >= static_cast<T>(0));

        if (value == static_cast<T>(0) || value == static_cast<T>(1))
        {
            return value;
        }

        T guess = value;
        T previousGuess;
        do
        {
            previousGuess = guess;
            guess = (guess + value / guess) / static_cast<T>(2);
        }
        while(Math::abs(guess - previousGuess) > precision);

        return guess;
    }

    template<typename T>
    constexpr bool equal(T value1, T value2, T precision = 1e-6f)
    {
        return Math::abs(value1 - value2) <= precision;
    }

    template<typename T>
    constexpr bool notEqual(T value1, T value2, T precision = 1e-6f)
    {
        return !Math::equal(value1, value2);
    }
}

#endif
