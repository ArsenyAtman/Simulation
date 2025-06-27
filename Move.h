#ifndef MOVE_H
#define MOVE_H

namespace Move
{
	template<typename T>
	struct removeRef
	{
		using type = T;
	};

	template<typename T>
	struct removeRef<T&>
	{
		using type = T;
	};

	template<typename T>
	struct removeRef<T&&>
	{
		using type = T;
	};

	template<typename T>
	using unref = typename removeRef<T>::type;

	template<typename T>
	constexpr unref<T>&& move(T&& value) { return static_cast<unref<T>&&>(value); }
}

#endif