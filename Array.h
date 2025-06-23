#ifndef ARRAY_H
#define ARRAY_H

#include "Size.h"

template <typename T>
class Array
{

public:
	
	Array(Size size = 10) : // TODO: use methods of the implementation here instead of hardcode
		allocationSize(size * (1.0f + allocationGap)),
		allocation(allocateNew(allocationSize)), // array of pointers
		lastIndex(-1)
	{
		// ...
	}

	~Array()
	{
		for (int i = 0; i <= lastIndex; ++i)
		{
			delete allocation[i];
		}
		delete[] allocation;
	}

	Size add(const T& element);
	Size remove(Size atIndex);
	const T& get(Size atIndex) const;
	T& get(Size atIndex);
	
	Size getLastIndex() const { return lastIndex; }
	Size length() const { return  getLastIndex() + 1; }

	Size getAllocationSize() const { return allocationSize; }

private:

	void checkAllocationSize();

	T** allocateNew(Size size);
	void transferAllocationTo(T** newAllocation, Size newAllocationSize);

	Size getRecommendedAllocationSize() const;

	Size allocationSize; // TODO: create an object for allocation
	T** allocation;
	Size lastIndex = -1;

	float allocationGap = 0.3f;
};

template<typename T>
Size Array<T>::add(const T& element)
{
	checkAllocationSize();

	++lastIndex;
	allocation[lastIndex] = new T(element);
	return lastIndex;
}

template<typename T>
Size Array<T>::remove(Size atIndex)
{
	if (atIndex >= 0 && atIndex <= lastIndex)
	{
		delete allocation[atIndex];

		for (int i = atIndex; i < lastIndex; ++i)
		{
			allocation[i] = allocation[i + 1];
		}
		--lastIndex;

		checkAllocationSize(); // TODO: combine reallocation and deletion

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
		return *allocation[atIndex];
	}

	throw "Invalid array index!";
}

template<typename T>
void Array<T>::checkAllocationSize()
{
	Size recommendedAllocationSize = getRecommendedAllocationSize();
	if (allocationSize != recommendedAllocationSize)
	{
		T** newAllocation = allocateNew(recommendedAllocationSize);
		transferAllocationTo(newAllocation, recommendedAllocationSize);
	}
}

template<typename T>
T** Array<T>::allocateNew(Size size)
{
	return new T*[size];
}

template<typename T>
void Array<T>::transferAllocationTo(T** newAllocation, Size newAllocationSize)
{
	for (int i = 0; i <= lastIndex; ++i)
	{
		newAllocation[i] = allocation[i];
	}

	delete[] allocation;
	allocation = newAllocation;
	allocationSize = newAllocationSize;
}

template<typename T>
Size Array<T>::getRecommendedAllocationSize() const
{
	if (lastIndex + 1 == allocationSize)
	{
		return allocationSize * (1.0f + allocationGap) + 1;
	}
	else if (lastIndex < allocationSize / (1.0f + allocationGap * 2.0f))
	{
		Size newSize = allocationSize / (1.0f + allocationGap);
		if (newSize < allocationSize)
		{
			return newSize;
		}
		else
		{
			return allocationSize;
		}
	}

	return allocationSize;
}

#endif
