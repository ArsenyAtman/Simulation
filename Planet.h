#ifndef PLANET_H
#define PLANET_H

#include "Vector.h"
#include "Math.h"
#include "PhysicsValues.h"

class Planet
{

public:

    constexpr Planet(float initialRadius, Vector initialPosition, Vector initialVelocity) :
        radius(initialRadius),
        mass(4.0f / 3.0f * Math::getPI() * Math::pow(radius, 3) * PhysicsValues::getPlanetDensity()),
        position(initialPosition),
        velocity(initialVelocity)
    {
        // ...
    }

    constexpr float getRadius() const { return radius; }
    constexpr float getMass() const { return mass; }

    constexpr const Vector& getPosition() const { return position; }
    constexpr const Vector& getVelocity() const { return velocity; }

    void update(const Vector& acceleraion, float deltaTime)
    {
        velocity = velocity + acceleraion * deltaTime;
        position = position + velocity * deltaTime;
    }

private:

    // TODO: initialization values
    float radius;
    float mass;

    Vector position;
    Vector velocity;

};

#endif
