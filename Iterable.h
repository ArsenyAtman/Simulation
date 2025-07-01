#ifndef ITERABLE_H
#define ITERABLE_H

#include "Iterator.h"
#include "IteratorWrap.h"

template<typename T>
class IIterable
{

public:

	virtual IIterator<T>* getIterator() = 0;
	virtual IConstIterator<T>* getConstIterator() const = 0;

	IteratorWrap<T> begin() { return IteratorWrap<T>(getIterator()); }
	ConstIteratorWrap<T> begin() const { return ConstIteratorWrap<T>(getConstIterator()); }

	void* end() const { return nullptr; }
};

#endif
