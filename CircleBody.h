#ifndef CIRCLE_BODY_H
#define CIRCLE_BODY_H

#include "RoundBody.h"

#include "Math.h"

class CircleBody : public RoundBody
{

public:

	constexpr CircleBody(float bodyRadius, float bodySquareDensity) :
		RoundBody(bodyRadius),
		squareDensity(bodySquareDensity)
	{
		// ...
	}

	float getSquareDensity() const { return squareDensity; }

	virtual float getMass() const override { return Math::getPI() * Math::pow(getRadius()); }

	virtual CircleBody* clone() const override { return new CircleBody(*this); }

private:

	float squareDensity; 

};

#endif
