#ifndef ROUND_BODY_H
#define ROUND_BODY_H

#include "Body.h"

class RoundBody : public Body
{

public:

	constexpr RoundBody(float bodyRadius) :
		radius(bodyRadius)
	{
		// ...
	}

	float getRadius() const { return radius; }

private:

	float radius;
};

#endif
