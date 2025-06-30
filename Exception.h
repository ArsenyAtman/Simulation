#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "String.h"

class Exception
{

public:

	Exception(const String& exceptionMessage) :
		message(exceptionMessage)
	{
		// ...
	}

	virtual ~Exception() = default;

	constexpr operator String () const { return message; }

private:

	String message;
};

class InvalidIndexException : public Exception
{
	
public:

	InvalidIndexException() :
		Exception("Invalid index!")
	{
		// ..
	}
};

#endif