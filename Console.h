#ifndef CONSOLE_H
#define CONSOLE_H

#include "Singleton.h"

#include "String.h"

#include "iostream"

inline std::ostream& operator << (std::ostream& out, const String& string)
{
	for (int i = 0; i < string.length(); ++i)
	{
		out << string.get(i);
	}

	return out;
}

class Console : public Singleton<Console>
{

public:

	Console() = default;

	static void print(const String& string) { Console::get().printString(string); }
	static void println(const String& string = "") { Console::get().printlnString(string); }

	void printString(const String& string) const { std::cout << string; }
	void printlnString(const String& string = "") const { std::cout << string << std::endl; }
};

#endif