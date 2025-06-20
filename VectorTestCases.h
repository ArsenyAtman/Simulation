#ifndef VECTOR_TEST_CASES_H
#define VECTOR_TEST_CASES_H

#include "Check.h"

#include "Vector.h"

namespace TestCases
{
    void checkVectorAdd()
    {
        Vector vector = Vector(3.0f, 3.0f);
        check("Vector addition", vector.add(vector), vector.scale(2.0f));
    }

    void checkVectorSub()
    {
        Vector vector = Vector(3.0f, 3.0f);
        check("Vector substraction", vector.sub(vector) == VectorLiterals::zeroVector);
    }

    void checkVectorScale()
    {
        Vector vectorOne = Vector(1.0f, 1.0f);
        Vector vector = Vector(3.0f, 3.0f);

        check("Vector scale length", vector.length() == vectorOne.scale(3.0f).length());
        check("Vector scale coords", vector == vectorOne.scale(3.0f));
    }

    void checkVectorNull()
    {
        Vector vector = VectorLiterals::xOneVector;
        vector.null();
        check("Vector null test", vector == VectorLiterals::zeroVector);
    }

    void checkVectorNormalize()
    {
        Vector vectorShort = Vector(1.0f, 1.0f);
        Vector vectorLong = Vector(3.0f, 3.0f);

        check("Vector normalize length", vectorShort.normalize(), vectorLong.normalize());
        check("Vector normalize length value", vectorLong.normalize().length(), 1.0f);
        check("Vector normalize direction", vectorShort.normalize().scale(vectorShort.length()), vectorShort);
    }

    void checkVectorLength()
    {
        Vector vector = Vector(3.0f, 4.0f);
        check("Vector length", vector.length() == 5.0f);
    }

    void checkVectorLengthSquared()
    {
        Vector vector = Vector(3.0f, 4.0f);
        check("Vector lengthSquared equality", vector.length() * vector.length() == vector.lengthSquared());
        check("Vector lengthSquared value", vector.lengthSquared() == 25.0f);
    }
}

#endif
