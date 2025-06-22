#ifndef ARRAY_H
#define ARRAY_H

#include "Size.h"

template <typename T>
class Array
{

public:
	
	Array()
	{
		// ...
	}

	Size add(const T& element);
	Size remove(Size atIndex);
	const T& get(Size atIndex) const;
	T& get(Size atIndex);
	
	Size getLastIndex() const { return lastIndex; }
	Size length() const { return  getLastIndex() + 1; }

private:

	static constexpr Size allocationSize = 100;
	T allocation[allocationSize] {}; // TODO: store array of pointers to pointers of allocations for single objects
	Size lastIndex = -1;
};

template<typename T>
Size Array<T>::add(const T& element)
{
	if (lastIndex < allocationSize)
	{
		++lastIndex;
		allocation[lastIndex] = element;
		return lastIndex;
	}
	
	return -1;
}

template<typename T>
Size Array<T>::remove(Size atIndex)
{
	if (atIndex >= 0 && atIndex <= lastIndex)
	{
		for (int i = atIndex; i < lastIndex; ++i)
		{
			allocation[i] = allocation[i + 1];
		}
		--lastIndex;
		return atIndex;
	}
	return -1;
}

template<typename T>
const T& Array<T>::get(Size atIndex) const
{
	if (atIndex >= 0 && atIndex <= lastIndex)
	{
		return allocation[atIndex];
	}
	
	throw "Invalid array index!";
}

template<typename T>
T& Array<T>::get(Size atIndex)
{
	if (atIndex >= 0 && atIndex <= lastIndex)
	{
		return allocation[atIndex];
	}

	throw "Invalid array index!";
}

#endif
