#ifndef PROTOTYPE_H
#define PROTOTYPE_H

template<typename T>
class IPrototype
{

public:

	virtual T* clone() const = 0;
};

#endif