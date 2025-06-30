#ifndef STRING_H
#define STRING_H

#include "Size.h"
#include "Exception.h"

#include <string>

// TODO: implement dynamic allocation
class String
{

public:

	constexpr String()
	{
		// ...
	}

	constexpr String(const char str[]) noexcept
	{
		while (str[size] != '\0' && size < allocationSize)
		{
			string[size] = str[size];
			++size;
		}
	}

	// TODO: own implementation of conversion
	constexpr String(int value) noexcept :
		String(std::to_string(value).c_str())
	{
		// ...
	}

	// TODO: own implementation of conversion
	constexpr String(double value) noexcept :
		String(std::to_string(value).c_str())
	{
		// ...
	}

	// copy
	// move

	constexpr char get(Size atIndex) const
	{
		if (atIndex >= 0 && atIndex < size)
		{
			return string[atIndex];
		}

		throw InvalidIndexException();
	}

	constexpr char& get(Size atIndex)
	{
		if (atIndex >= 0 && atIndex < size)
		{
			return string[atIndex];
		}

		throw InvalidIndexException();
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

	constexpr void append(const String& other)
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

	constexpr String& operator += (const String& other)
	{
		this->append(other);
		return *this;
	}

private:

	static constexpr Size allocationSize = 100;
	char string[allocationSize] {};
	Size size = 0;
};

constexpr String operator + (const String& string1, const String& string2)
{
	String newString = string1;
	newString.append(string2);
	return newString;
}

#endif STRING_H

