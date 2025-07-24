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

#ifndef AHI_LCG_H
#define AHI_LCG_H

#include <cstddef>

struct LCG {
	constexpr LCG() = default;
	constexpr void init(this LCG &self, std::size_t s) {
		self.seed = s;
	}
	constexpr size_t operator()(this LCG &self) {
		self.seed = self.seed * 7 + 3;
		return self.seed;
	}
private:
	std::size_t seed{};
};

#endif
