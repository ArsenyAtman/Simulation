#ifndef STRING_TEST_CASES
#define STRING_TEST_CASES

#include "String.h"
#include "Check.h"

namespace TestCases
{
	void checkStringIndexing()
	{
		String string;

		for (int i = 0; i < 10; ++i)
		{
			string.add(static_cast<char>('A' + i));
		}

		bool allEqual = true;
		for (int i = 0; i < 5; ++i)
		{
			if (string.get(i) != static_cast<char>('A' + i))
			{
				check("String indexing", false);
				return;
			}
		}

		check("String indexing", true);
	}

	void checkStringIteration()
	{
		check("String iteration", false);
	}

	void checkStringConcatenation()
	{
		String string1("Hello ");
		String string2("world!");

		string1.append(string2);

		check("String concatenation", string1, String("Hello world!"));
	}

	void checkStringCopy()
	{
		check("String copy", false);
	}

	void checkStringMove()
	{
		check("String move", false);
	}
}

#endif