#ifndef PHYSICS_H
#define PHYSICS_H

namespace Physics
{
    constexpr float calculateGravityForce(float G, float mass1, float mass2, float squareDistance) { return G * mass1 * mass2 / squareDistance; }

    constexpr float calculateAcceleration(float force, float mass) { return force / mass; }

    constexpr float calculateDeltaSpeed(float acceleration, float deltaTime) { return acceleration * deltaTime; }

    constexpr float calculateTraveledDistance(float speed, float deltaTime) { return speed * deltaTime; }

    // TODO: Volume
}

#endif
