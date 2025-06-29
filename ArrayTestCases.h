#ifndef ARRAY_TEST_CASES_H
#define ARRAY_TEST_CASES_H

#include "Array.h"

#include "Check.h"

namespace TestCases
{
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
		check("Array iteration", false);
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

	// TODO: check filling of an array with the default allocation size

	// TODO: check removing only 0 index

	void checkArraySwap()
	{
		Array<int> array1;
		for (int i = 0; i < 10; ++i)
		{
			array1.add(i);
		}

		for (int i = 0; i < array1.length() / 2; ++i)
		{
			array1.swap(i, array1.getLastIndex() - i);
		}

		Array<int> controlArray;
		for (int i = 9; i >= 0; --i)
		{
			controlArray.add(i);
		}

		check("Array swap", array1, controlArray);
	}

	void checkArrayAppend()
	{
		Array<int> array1;
		for (int i = 0; i < 5; ++i)
		{
			array1.add(i);
		}

		Array<int> array2;
		for (int i = 5; i < 10; ++i)
		{
			array2.add(i);
		}

		array1.append(array2);

		Array<int> controlArray;
		for (int i = 0; i < 10; ++i)
		{
			controlArray.add(i);
		}

		check("Array append", array1, controlArray);
	}

	void checkArrayConcatenate()
	{
		Array<int> array1;
		for (int i = 0; i < 5; ++i)
		{
			array1.add(i);
		}

		Array<int> array2;
		for (int i = 5; i < 10; ++i)
		{
			array2.add(i);
		}

		array1 = array1.concatenate(array2);

		Array<int> controlArray;
		for (int i = 0; i < 10; ++i)
		{
			controlArray.add(i);
		}

		check("Array concatenate", array1, controlArray);
	}

	// TODO: memory leaks test

	void checkArrayRemove()
	{
		Array<int> array(0);
		for (int i = 0; i < 5; ++i)
		{
			array.add(i);
		}

		for (int i = array.getLastIndex(); i >= 0; --i)
		{
			array.remove(i);
		}

		check("Array remove index", array.getLastIndex(), -1);
		check("Array remove length", array.length(), 0);
	}

	void checkArrayCopy()
	{
		check("Array copy", false);
	}

	void checkArrayMove()
	{
		check("Array move", false);
	}

	void checkArraySort()
	{
		Array<int> array;
		for (int i = 10; i >= 0; --i)
		{
			array.add(i);
		}

		auto sortCondition{ [](int a, int b)
		{
			return a < b;
		} };

		array.sort(sortCondition);

		for (int i = 0; i <= 10; ++i)
		{
			if (array.get(i) != i)
			{
				check("Array sort", array.get(i), i);
				return;
			}
		}

		check("Array sort", true);
	}
}

#endif