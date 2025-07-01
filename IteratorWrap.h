#ifndef ITERATOR_WRAP_H
#define ITERATOR_WRAP_H

template<typename T>
class IteratorWrap
{

public:

	IteratorWrap(IIterator<T>* wrappedIterator) :
		iterator(wrappedIterator)
	{
		// ...
	}

	virtual ~IteratorWrap()
	{
		delete iterator;
	}

	// Forbid copying
	IteratorWrap(const IteratorWrap& other) = delete;
	IteratorWrap& operator = (const IteratorWrap& other) = delete;

	IteratorWrap(IteratorWrap&& other) :
		iterator(other.iterator)
	{
		other.iterator = nullptr;
	}

	IteratorWrap& operator = (IteratorWrap&& other)
	{
		delete iterator;

		iterator = other.iterator;
	}

	void operator ++ ()
	{
		iterator->next();
	}

	bool operator != (void*) const
	{
		return iterator->hasMore();
	}

	T& operator * ()
	{
		return iterator->get();
	}

private:

	IIterator<T>* iterator;
};

template<typename T>
class ConstIteratorWrap
{

public:

	ConstIteratorWrap(IConstIterator<T>* wrappedIterator) :
		iterator(wrappedIterator)
	{
		// ...
	}

	virtual ~ConstIteratorWrap()
	{
		delete iterator;
	}

	void operator ++ ()
	{
		iterator->next();
	}

	bool operator != (void*) const
	{
		return iterator->hasMore();
	}

	const T& operator * () const
	{
		return iterator->get();
	}

private:

	IConstIterator<T>* iterator;
};

#endif