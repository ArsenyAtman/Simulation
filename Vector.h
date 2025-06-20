#ifndef VECTOR_H
#define VECTOR_H

#include "Math.h"

#include <iostream>

// TODO: operator overload
class Vector
{

public:

    float x;
    float y;

    explicit constexpr Vector(float xValue, float yValue) :
        x(xValue),
        y(yValue)
    {
        // ...
    }

    constexpr Vector add(const Vector& vector) const
    {
        return Vector(x + vector.x, y + vector.y);
    }

    constexpr Vector sub(const Vector& vector) const
    {
        return Vector(x - vector.x, y - vector.y);
    }

    constexpr Vector scale(float scale) const
    {
        return Vector(x * scale, y * scale);
    }

    constexpr Vector& null()
    {
        return *this = Vector(0.0f, 0.0f);
    }

    constexpr float lengthSquared() const
    {
        return x * x + y * y;
    }

    constexpr float length() const
    {
        return Math::sqrt(lengthSquared());
    }

    constexpr Vector normalize() const
    {
        return this->scale(1.0f / this->length());
    }

    constexpr bool operator == (const Vector& other) const
    {
        return Math::equal(x, other.x) && Math::equal(y, other.y);
    }
};

inline std::ostream& operator << (std::ostream& cout, const Vector& vector)
{
    cout << "Vector(" << vector.x << ", " << vector.y << ")";
    return cout;
}

namespace VectorLiterals
{
    constexpr Vector zeroVector = Vector(0.0f, 0.0f);
    constexpr Vector xOneVector = Vector(1.0f, 0.0f);
    constexpr Vector yOneVector = Vector(0.0f, 1.0f);
}

#endif
