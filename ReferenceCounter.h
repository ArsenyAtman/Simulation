#ifndef REFERENCE_COUNTER_H
#define REFERENCE_COUNTER_H

#include "Size.h"

class ReferenceCounter
{

public:

	ReferenceCounter() :
		countOfReferencesToResource(1),
		countOfReferencesToCounter(1)
	{
		// ...
	}

	// Forbid copying
	ReferenceCounter(const ReferenceCounter& other) = delete;

	void addStrongReference()
	{
		++countOfReferencesToResource;
		++countOfReferencesToCounter;
	}

	void addWeakReference()
	{
		++countOfReferencesToCounter;
	}

	void removeSharedReference()
	{
		--countOfReferencesToResource;
		--countOfReferencesToCounter;
	}

	void removeWeakReference()
	{
		--countOfReferencesToCounter;
	}

	bool isValidResource() const { return countOfReferencesToResource > 0; }
	bool isValidCounter() const { return countOfReferencesToCounter > 0; }

private:

	Size countOfReferencesToResource;
	Size countOfReferencesToCounter;
};

#endif