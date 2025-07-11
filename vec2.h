#ifndef AHI_VEC2_H
#define AHI_VEC2_H

template <typename T>
struct Vec2 {
	T x;
	T y;
	constexpr Vec2() : x{}, y{} {}
	constexpr Vec2(T x, T y) : x{x}, y{y} {};
	constexpr bool operator== (const Vec2<T> &other) const = default;
};

#endif
