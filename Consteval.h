#ifndef CONSTEVAL_H
#define CONSTEVAL_H

// garantees that a constexpr function will be evalueated in compile-time (C++11 version)
#define CONSTEVAL(...) [] { constexpr auto = __VA_ARGS__; return _; }()

// garantees that a constexpr function will be evalueated in compile-time (C++20 version)
//consteval auto CONSTEVAL(auto value) { return value; }

#endif
