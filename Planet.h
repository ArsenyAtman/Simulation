#ifndef PLANET_H
#define PLANET_H

#include "Object.h"
#include "Prototype.h"

#include "Vector.h"
#include "Math.h"
#include "PhysicsValues.h"
#include "Body.h"
#include "UniquePointer.h"
#include "Move.h"

#include <utility>

class Planet : public Object, public IPrototype<Planet>
{

public:

    Planet(Vector initialPosition, UniquePointer<Body> planetBody, Vector initialVelocity) :
        Object(initialPosition),
        body(MOVE(planetBody)),
        velocity(initialVelocity)
    {
        // ...
    }

    Planet(const Planet& other) noexcept :
        Object(other.getPosition()),
        body(other.body->clone()),
        velocity(other.getVelocity())
    {
        // ...
    }

    Planet(Planet&& other) noexcept :
        Object(other.getPosition()),
        body(MOVE(other.body)),
        velocity(other.getVelocity())
    {
        // ...
    }

    Planet& operator = (const Planet& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        Object::operator=(other);
        body = UniquePointer(other.body->clone());
        velocity = other.velocity;

        return *this;
    }

    Planet& operator = (Planet&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        Object::operator=(MOVE(other));
        body = MOVE(other.body);
        velocity = other.velocity;

        return *this;
    }

    const UniquePointer<Body>& getBody() const { return body; }
    const Vector& getVelocity() const { return velocity; }

    void update(const Vector& acceleraion, float deltaTime)
    {
        velocity = velocity + acceleraion * deltaTime;
        setPosition(getPosition() + velocity * deltaTime);
    }

    virtual Planet* clone() const override { return new Planet(*this); }

private:

    UniquePointer<Body> body;

    Vector velocity;

};

#endif
