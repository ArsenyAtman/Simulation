#ifndef SPHERE_BODY_H
#define SPHERE_BODY_H

#include "RoundBody.h"

#include "Math.h"

class SphereBody : public RoundBody
{

public:

	constexpr SphereBody(float bodyRadius, float bodyDensity) :
		RoundBody(bodyRadius),
		density(bodyDensity)
	{
		// ...
	}

	float getDensity() const { return density; }

	virtual float getMass() const override { return 4.0f / 3.0f * Math::getPI() * Math::pow(getRadius(), 3) * getDensity(); }

private:

	float density;
};

#endif
