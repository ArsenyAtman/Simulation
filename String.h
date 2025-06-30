#ifndef STRING_H
#define STRING_H

#include "Size.h"

#include <string>

// TODO: implement dynamic allocation
class String
{

public:

	constexpr String();
	constexpr String(const char str[]) noexcept;

	// TODO: own implementation of conversions
	constexpr String(int value) noexcept;
	constexpr String(double value) noexcept;

	// copy
	// move

	constexpr char get(Size atIndex) const;
	constexpr char& get(Size atIndex);

	constexpr Size add(char newChar);
	constexpr void append(const String& other);

	constexpr Size length() const { return size; }

	constexpr bool operator == (const String& other) const;

	constexpr String& operator += (const String& other);

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

#include "InvalidIndexException.h"

constexpr String::String()
{
	// ...
}

constexpr String::String(const char str[]) noexcept
{
	while (str[size] != '\0' && size < allocationSize)
	{
		string[size] = str[size];
		++size;
	}
}

constexpr String::String(int value) noexcept :
	String(std::to_string(value).c_str())
{
	// ...
}

constexpr String::String(double value) noexcept :
	String(std::to_string(value).c_str())
{
	// ...
}

constexpr char String::get(Size atIndex) const
{
	if (atIndex >= 0 && atIndex < size)
	{
		return string[atIndex];
	}

	throw InvalidIndexException();
}

constexpr char& String::get(Size atIndex)
{
	if (atIndex >= 0 && atIndex < size)
	{
		return string[atIndex];
	}

	throw InvalidIndexException();
}

constexpr Size String::add(char newChar)
{
	if (size < allocationSize)
	{
		string[size] = newChar;
		return ++size;
	}

	return -1;
}

constexpr void String::append(const String& other)
{
	for (int i = 0; i < other.length(); ++i)
	{
		this->add(other.get(i));
	}
}

constexpr bool String::operator == (const String& other) const
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

constexpr String& String::operator += (const String& other)
{
	this->append(other);
	return *this;
}

#endif STRING_H

