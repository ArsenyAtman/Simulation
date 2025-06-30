#ifndef INVALID_INDEX_EXCEPTION_H
#define INVALID_INDEX_EXCEPTION_H

#include "Exception.h"

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