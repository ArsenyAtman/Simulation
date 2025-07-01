#ifndef ARRAY_TEST_CASES_H
#define ARRAY_TEST_CASES_H

#include "Array.h"
#include "SharedPointer.h"

#include "Check.h"

namespace TestCases
{
	// TODO: check filling of an array with the default allocation size

	// TODO: check removing only 0 index

	// TODO: memory leaks test

	class TestResource {
	public:
		int& allocationCounter;
		int& destructionCounter;
		TestResource(int& allocCounterRef, int& destrCounterRef) :
			allocationCounter(allocCounterRef),
			destructionCounter(destrCounterRef)
		{
			++allocationCounter;
		}

		TestResource(const TestResource& other) :
			allocationCounter(other.allocationCounter),
			destructionCounter(other.destructionCounter)
		{
			++allocationCounter;
		}

		~TestResource()
		{
			++destructionCounter;
		}

		constexpr operator String() const
		{
			return "TestResource()";
		}

		constexpr bool operator == (const TestResource& other) const
		{
			return (&allocationCounter == &other.allocationCounter) && (&destructionCounter == &other.destructionCounter);
		}

		constexpr bool operator != (const TestResource& other) const
		{
			return !(*this == other);
		}
	};

	void checkArrayIndexing()
	{
		Array<int> array(0);
		for (int i = 0; i < 5; ++i)
		{
			array.add(i);
		}

		for (int i = 0; i < 5; ++i)
		{
			if (array.get(i) != i)
			{
				check("Array indexing", false);
				return;
			}
		}

		check("Array indexing", true);
	}

	void checkArrayAllocationOpt()
	{
		Array<int> array(0);
		int prevAllocationSize = array.getAllocationSize();
		for (int i = 0; i < 50; ++i)
		{
			array.add(i);

			if (prevAllocationSize > array.getAllocationSize())
			{
				check("Array allocation optimization", false);
			}

			prevAllocationSize = array.getAllocationSize();
		}

		check("Array allocation optimization", true);
	}

	void checkArrayIteration()
	{
		Array<int> array = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int counter = 0;
		for (const int& element : array)
		{
			if (element != counter)
			{
				check("Array iteration", element, static_cast<Size>(&element - &array[0]));
			}
			
			++counter;
		}

		check("Array iteration", true);
	}

	void checkArrayAdd()
	{
		Array<int> array(0);
		for (int i = 0; i < 5; ++i)
		{
			array.add(i);
		}

		check("Array add index", array.getLastIndex(), 4);
		check("Array add length", array.length(), 5);
	}

	void checkArraySwap()
	{
		Array<int> array1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		for (int i = 0; i < array1.length() / 2; ++i)
		{
			array1.swap(i, array1.getLastIndex() - i);
		}

		Array<int> expectedArray = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
		check("Array swap", array1, expectedArray);
	}

	void checkArrayAppend()
	{
		Array<int> array1 = { 0, 1, 2, 3, 4 };
		Array<int> array2 = { 5, 6, 7, 8, 9 };

		array1.append(array2);

		Array<int> expectedArray = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		check("Array append", array1, expectedArray);
	}

	void checkArrayConcatenate()
	{
		Array<int> array1 = { 0, 1, 2, 3, 4 };
		Array<int> array2 = { 5, 6, 7, 8, 9 };

		array1 = array1.concatenate(array2);

		Array<int> expectedArray = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		check("Array concatenate", array1, expectedArray);
	}

	void checkArrayRemove()
	{
		Array<int> array = { 0, 1, 2, 3, 4 };

		for (int i = array.getLastIndex(); i >= 0; --i)
		{
			array.remove(i);
		}

		check("Array remove index", array.getLastIndex(), -1);
		check("Array remove length", array.length(), 0);
	}

	void checkArrayCopy()
	{
		int allocationCounter = 0;
		int destructionCounter = 0;

		{
			Array<SharedPointer<TestResource>> array = {
				SharedPointer<TestResource>(new TestResource(allocationCounter, destructionCounter)),
				SharedPointer<TestResource>(new TestResource(allocationCounter, destructionCounter)),
				SharedPointer<TestResource>(new TestResource(allocationCounter, destructionCounter))
			};

			int sourceArrayLength = array.length();

			Array<SharedPointer<TestResource>> newArray(array);

			int expectedCountOfAllocations = array.length();
			int expectedCountOfDestructions = 0;

			check("Array copy allocations", allocationCounter, expectedCountOfAllocations);
			check("Array copy destructions", destructionCounter, expectedCountOfDestructions);
			check("Array copy content", newArray, array);
			check("Array copy content length", newArray.length(), sourceArrayLength);
		}

		check("Array copy mem leak", destructionCounter, allocationCounter);
	}

	void checkArrayMove()
	{
		int allocationCounter = 0;
		int destructionCounter = 0;

		{
			Array<SharedPointer<TestResource>> array = {
				SharedPointer<TestResource>(new TestResource(allocationCounter, destructionCounter)),
				SharedPointer<TestResource>(new TestResource(allocationCounter, destructionCounter)),
				SharedPointer<TestResource>(new TestResource(allocationCounter, destructionCounter))
			};

			int sourceArrayLength = array.length();

			int expectedCountOfAllocations = array.length();
			int expectedCountOfDestructions = 0;

			Array<SharedPointer<TestResource>> newArray(MOVE(array));

			check("Array move allocations", allocationCounter, expectedCountOfAllocations);
			check("Array move destructions", destructionCounter, expectedCountOfDestructions);
			check("Array moved content", newArray.length(), sourceArrayLength);
			check("Array removed content", array.length(), 0);
		}

		check("Array move mem leak", destructionCounter, allocationCounter);
	}

	void checkArraySort()
	{
		Array<int> array = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

		auto sortCondition{ [](int a, int b)
		{
			return a < b;
		} };

		array.sort(sortCondition);

		Array<int> expectedArray = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		check("Array sort", array, expectedArray);
	}
}

#endif