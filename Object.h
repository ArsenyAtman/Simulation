#ifndef OBJECT_H
#define OBJECT_H

#include "Vector.h"

class Object
{

public:

	constexpr Object(const Vector& objectPosition) :
		position(objectPosition)
	{
		// ...
	}

	const Vector& getPosition() const { return position; }
	void setPosition(const Vector& newPosition) { position = newPosition; }

private:

	Vector position;
};

#endif