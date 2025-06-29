#ifndef BODY_H
#define BODY_H

class Body
{

public:

	virtual ~Body() = default;

	virtual float getMass() const = 0;

	virtual float getSize() const = 0;
};

#endif