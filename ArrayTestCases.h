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

		bool allEqual = true;
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
}

#endif