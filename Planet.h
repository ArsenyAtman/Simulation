#ifndef PLANET_H
#define PLANET_H

#include "Object.h"

#include "Vector.h"
#include "Math.h"
#include "PhysicsValues.h"
#include "Body.h"
#include "UniquePointer.h"
#include "Move.h"

#include <utility>

class Planet : public Object
{

public:

    Planet(Vector initialPosition, UniquePointer<Body> planetBody, Vector initialVelocity) :
        Object(initialPosition),
        body(MOVE(planetBody)),
        velocity(initialVelocity)
    {
        // ...
    }

    const UniquePointer<Body>& getBody() const { return body; }
    const Vector& getVelocity() const { return velocity; }

    void update(const Vector& acceleraion, float deltaTime)
    {
        velocity = velocity + acceleraion * deltaTime;
        setPosition(getPosition() + velocity * deltaTime);
    }

private:

    UniquePointer<Body> body;

    Vector velocity;

};

#endif
