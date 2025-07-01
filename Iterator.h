#ifndef ITERATOR_H
#define ITERATOR_H

template<typename T>
class IIteratorBase
{

public:

	IIteratorBase() = default;
	virtual ~IIteratorBase() = default;

	virtual bool hasMore() const = 0;
	virtual bool next() = 0;
};

template<typename T>
class IIterator : public IIteratorBase<T>
{

public:

	virtual T& get() = 0;
};

template<typename T>
class IConstIterator : public IIteratorBase<T>
{

public:

	virtual const T& get() const = 0;
};

#endif