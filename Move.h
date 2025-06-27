#ifndef MOVE_H
#define MOVE_H

#define MOVE(...) static_cast<Move::unref<decltype(__VA_ARGS__)>&&>(__VA_ARGS__)

namespace Move
{
	template<typename T>
	struct removeRef
	{
		using type = T;
	};

	template<typename T>
	struct removeRef<T&> // specialization for refs
	{
		using type = T;
	};

	template<typename T>
	struct removeRef<T&&> // specialization for r-values
	{
		using type = T;
	};

	template<typename T>
	using unref = typename removeRef<T>::type; // shorthand
}

#endif