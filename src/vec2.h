/* ahi is a simple snake game written in C++
 *
 * Copyright (C) 2025  Farid Farajli
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef AHI_VEC2_H
#define AHI_VEC2_H

#include <cstdint>

template <typename T>
struct Vec2 {
	T x{};
	T y{};
	constexpr Vec2() = default;
	constexpr Vec2(T x_, T y_) : x{x_}, y{y_} {};
	constexpr bool operator==(const Vec2<T> &other) const = default;
};

using Direction = Vec2<int>;
using Position = Vec2<uint64_t>;

#endif
