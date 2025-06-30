#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "String.h"


// TODO: implement projectwise
class Exception
{

public:

	Exception(const String& exceptionMessage) :
		message(exceptionMessage)
	{
		// ...
	}

	virtual ~Exception() = default;

	virtual String toString() const { return message; }

private:

	String message;
};

#endif