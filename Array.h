#ifndef ARRAY_H
#define ARRAY_H

#include "Size.h"

#include "iostream"

template <typename T>
class Array
{

public:

	using SortCondition = bool(*)(T a, T b);
	using PickCondition = bool(*)(T element);
	
	Array(Size size = 10);
	Array(const Array<T>& other); // copy constructor
	Array(Array<T>&& other); // move constructor

	Array<T>& operator = (const Array<T>& other); // copy operator
	Array<T>& operator = (Array<T>&& other); // move operator

	~Array();

	Size add(const T& element);
	Size remove(Size atIndex);

	Array<T>& append(const Array<T>& other);
	Array<T> concatenate(const Array<T>& other) const;

	bool equal(const Array<T>& other) const;

	const T& get(Size atIndex) const;
	T& get(Size atIndex);

	const T& operator [] (Size index) const { return this->get(index); }
	T& operator [] (Size index) { return this->get(index); }
	Array<T> operator + (const Array<T>& other) const { return this->concatenate(other); }

	bool operator == (const Array<T>& other) const { return this->equal(other); }

	// equal

	//Size removeFirst(const T& value);
	//Size removeAll(const T& value);

	// removeFirstByPrediacte
	// removeAllByPredicate

	// findFirst
	// findFirstByPredicate
	// findAllByPredicate
	// 
	// Count
	
	Size getLastIndex() const { return lastIndex; }
	Size length() const { return  getLastIndex() + 1; }

	Size getAllocationSize() const { return allocationSize; }

	void sort(Array::SortCondition condition = [](T a, T b) { return a < b; });

	void swap(Size atIndex1, Size atIndex2);

private:

	void checkAllocationSize();

	T** allocateNew(Size size);
	void deleteAllocation();
	void transferAllocationTo(T** newAllocation, Size newAllocationSize);

	Size getRecommendedAllocationSize() const;

	Size allocationSize;
	T** allocation;
	Size lastIndex = -1;

	float allocationGap = 0.3f;
};

template<typename T>
std::ostream& operator << (std::ostream& out, const Array<T>& array)
{
	out << "Array: {";
	for (int i = 0; i < array.length(); ++i)
	{
		out << array[i];
		if (i != array.getLastIndex())
		{
			out << ", ";
		}
	}
	out << "}";

	return out;
}

template<typename T>
Array<T>::Array(Size size) :
	allocationSize(size * static_cast<Size>(1.0f + allocationGap)),
	allocation(allocateNew(allocationSize))
{
	// ...
}

template<typename T>
Array<T>::Array(const Array<T>& other) :
	allocationSize(other.allocationSize),
	allocation(allocateNew(allocationSize)),
	lastIndex(other.lastIndex)
{
	for (int i = 0; i <= lastIndex; ++i)
	{
		allocation[i] = new T(*(other.allocation[i]));
	}
}

template<typename T>
Array<T>::Array(Array<T>&& other) :
	allocationSize(other.allocationSize),
	allocation(other.allocation),
	lastIndex(other.lastIndex)
{
	other.allocationSize = 0;
	other.allocation = nullptr;
	other.lastIndex = -1;
}

template<typename T>
Array<T>& Array<T>::operator = (const Array<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	deleteAllocation();

	allocationSize = other.allocationSize;
	lastIndex = other.lastIndex;

	allocation = allocateNew(allocationSize);

	for (int i = 0; i <= lastIndex; ++i)
	{
		allocation[i] = new T(*(other.allocation[i]));
	}

	return *this;
}

template<typename T>
Array<T>& Array<T>::operator = (Array<T>&& other)
{
	if (this == &other)
	{
		return *this;
	}

	allocationSize = other.allocationSize;
	allocation = other.allocation;
	lastIndex = other.lastIndex;

	other.allocationSize = 0;
	other.allocation = nullptr;
	other.lastIndex = -1;

	return *this;
}

template<typename T>
Array<T>::~Array()
{
	deleteAllocation();
}

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
Array<T>& Array<T>::append(const Array<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (other.length() == 0)
	{
		return *this;
	}

	Size newAllocationSize = this->allocationSize + other.allocationSize;
	T** newAllocation = allocateNew(newAllocationSize);

	for (int i = 0; i < this->length(); ++i)
	{
		newAllocation[i] = new T(*(this->allocation[i]));
	}

	for (int i = 0; i < other.length(); ++i)
	{
		newAllocation[this->length() + i] = new T(*(other.allocation[i]));
	}

	delete[] allocation;
	this->allocation = newAllocation;
	this->allocationSize = newAllocationSize;
	this->lastIndex = this->length() + other.lastIndex;
	return *this;
}

template<typename T>
Array<T> Array<T>::concatenate(const Array<T>& other) const
{
	if (this == &other)
	{
		return *this;
	}

	if (other.length() == 0)
	{
		return *this;
	}

	Array<T> newArray(this->length() + other.length());
	newArray = *this;
	newArray.append(other);

	return newArray;
}

template<typename T>
bool Array<T>::equal(const Array<T>& other) const
{
	if (this == &other)
	{
		return true;
	}

	if (this->length() != other.length())
	{
		return false;
	}

	for (int i = 0; i <= this->lastIndex; ++i)
	{
		if (this->get(i) != other.get(i))
		{
			return false;
		}
	}

	return true;
}

template<typename T>
const T& Array<T>::get(Size atIndex) const
{
	if (atIndex >= 0 && atIndex <= lastIndex)
	{
		return *allocation[atIndex];
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
void Array<T>::deleteAllocation()
{
	for (int i = 0; i <= lastIndex; ++i)
	{
		delete allocation[i];
	}
	delete[] allocation;
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
		return static_cast<Size>(allocationSize * (1.0f + allocationGap) + 1);
	}
	else if (lastIndex < allocationSize / (1.0f + allocationGap * 2.0f))
	{
		Size newSize = static_cast<Size>(allocationSize / (1.0f + allocationGap));
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

template<typename T>
void Array<T>::sort(Array<T>::SortCondition condition) // TODO: implement quick sort
{
	for (int i = 0; i < this->length(); ++i)
	{
		for (int j = 0; j < this->length(); ++j)
		{
			if (condition(this->get(i), this->get(j)))
			{
				this->swap(i, j);
			}
		}
	}
}

template<typename T>
void Array<T>::swap(Size atIndex1, Size atIndex2)
{
	if ((atIndex1 != atIndex2) && (atIndex1 >= 0 && atIndex1 <= lastIndex) && (atIndex2 >= 0 && atIndex2 <= lastIndex))
	{
		T* cup = allocation[atIndex1];
		allocation[atIndex1] = allocation[atIndex2];
		allocation[atIndex2] = cup;
	}
}

#endif
