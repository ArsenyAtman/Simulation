#ifndef BODY_H
#define BODY_H

#include "Prototype.h"

class Body : public IPrototype<Body>
{

public:

	virtual ~Body() = default;

	virtual float getMass() const = 0;

	virtual float getSize() const = 0;
};

#endif