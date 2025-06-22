#include "Planet.h"
#include "Vector.h"
#include "Math.h"
#include "Physics.h"
#include "PhysicsValues.h"
#include "Tests.h"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>

constexpr float timeScale = 10000.0f;


Planet planets[] = {
    Planet(10.0f, Vector(50.0f, 150.0f), VectorLiterals::xOneVector.scale(0.0075f)),
    Planet(30.0f, Vector(50.0f, 300.f), VectorLiterals::zeroVector)
    };

constexpr int countOfPlanets = sizeof(planets) / sizeof(Planet);

sf::CircleShape planetCircles[countOfPlanets];

void initCircles()
{

    sf::CircleShape* planetCirclesPtr = planetCircles;
    sf::CircleShape* planetCirclesEndPtr = planetCircles + countOfPlanets;
    for ( ; planetCirclesPtr < planetCirclesEndPtr; ++planetCirclesPtr)
    {
        *(planetCirclesPtr) = sf::CircleShape((planets + (planetCirclesPtr - planetCircles))->getRadius());
        (planetCirclesPtr)->setFillColor(sf::Color::Black);
    }
}

// TODO: substepping
void calculatePlanets(float tick = 1.0f)
{
    for (Planet& planet : planets)
    {
        Vector planetAcceleration = VectorLiterals::zeroVector;

        for (const Planet& relativePlanet : planets)
        {
            if (&planet == &relativePlanet)
            {
                continue;
            }

            Vector distance = relativePlanet.getPosition().sub(planet.getPosition());
            float distanceSquared = distance.lengthSquared();

            float F = 0.0f;
            float dangerousDistance = Math::min(planet.getRadius(), relativePlanet.getRadius());
            if (distanceSquared > Math::pow(dangerousDistance))
            {
                F = Physics::calculateGravityForce(PhysicsValues::getG(), planet.getMass(), relativePlanet.getMass(), distanceSquared);
            }

            Vector relativeAcceleration = distance.normalize().scale(F).scale(1.0f / planet.getMass());
            planetAcceleration = planetAcceleration.add(relativeAcceleration);
        }

        planet.update(planetAcceleration, tick);
    }
}

void drawCircles(sf::RenderWindow& window)
{
    for (int i = 0; i < countOfPlanets; ++i)
    {
        planetCircles[i].setPosition({ planets[i].getPosition().x, planets[i].getPosition().y });
        window.draw(planetCircles[i]);
    }
}

int main()
{
    Tests::runTests();

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Space simulation");

    initCircles();

    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;
    using Point = std::chrono::time_point<Clock>;

    Point prev = Clock::now();

	// Start the game loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        double deltaTime = std::chrono::duration_cast<Second>(Clock::now() - prev).count();
        prev = Clock::now();

        calculatePlanets(static_cast<float>(deltaTime * timeScale));

        // Clear screen
        window.clear(sf::Color::White);

        drawCircles(window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
