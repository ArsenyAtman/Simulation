#ifndef STRING_H
#define STRING_H

#include "Size.h"

#include "iostream"

class String
{

public:

	constexpr String()
	{
		// ...
	}

	constexpr String(const char str[])
	{
		while (str[size] != '\0' && size < allocationSize)
		{
			string[size] = str[size];
			++size;
		}
	}

	constexpr char get(Size atIndex) const
	{
		if (atIndex >= 0 && atIndex < size)
		{
			return string[atIndex];
		}

		throw "Invalid string index!";
	}

	constexpr char& get(Size atIndex)
	{
		if (atIndex >= 0 && atIndex < size)
		{
			return string[atIndex];
		}

		throw "Invalid string index!";
	}

	Size add(char newChar)
	{
		if (size < allocationSize)
		{
			string[size] = newChar;
			return ++size;
		}
		
		return -1;
	}

	void append(const String& other)
	{
		for (int i = 0; i < other.length(); ++i)
		{
			this->add(other.get(i));
		}
	}

	constexpr Size length() const { return size; }

	constexpr bool operator == (const String& other) const
	{
		if (this->length() != other.length())
		{
			return false;
		}

		for (int i = 0; i < this->length(); ++i)
		{
			if (this->get(i) != other.get(i))
			{
				return false;
			}
		}

		return true;
	}

private:

	static constexpr Size allocationSize = 100;
	char string[allocationSize] {};
	Size size = 0;
};

inline std::ostream& operator << (std::ostream& cout, const String& string)
{
	for (int i = 0; i < string.length(); ++i)
	{
		cout << string.get(i);
	}

	return cout;
}

#endif STRING_H

