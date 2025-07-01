#ifndef ARRAY_ITERATOR_H
#define ARRAY_ITERATOR_H

#include "Iterator.h"
#include "Array.h"

// TODO: remove code duplication

template<typename T>
class ArrayIterator : public IIterator<T>
{

public:

	ArrayIterator(Array<T>& relatedArray) :
		array(relatedArray),
		currentIndex(0)
	{
		// ...
	}

	virtual bool hasMore() const override { return array.getLastIndex() != currentIndex; }
	virtual bool next() override
	{
		if (hasMore())
		{
			++currentIndex;
			return true;
		}

		return false;
	}

	virtual T& get() { return array[currentIndex]; }

private:

	Array<T>& array;
	int currentIndex;
};

template<typename T>
class ArrayConstIterator : public IConstIterator<T>
{

public:

	ArrayConstIterator(const Array<T>& relatedArray) :
		array(relatedArray),
		currentIndex(0)
	{
		// ...
	}

	virtual bool hasMore() const override { return array.getLastIndex() != currentIndex; }
	virtual bool next() override
	{
		if (hasMore())
		{
			++currentIndex;
			return true;
		}

		return false;
	}

	virtual const T& get() const { return array[currentIndex]; }

private:

	const Array<T>& array;
	int currentIndex;
};

#endif