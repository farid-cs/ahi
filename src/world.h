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

#ifndef AHI_WORLD_H
#define AHI_WORLD_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <random>
#include <ranges>

#include "lcg.h"
#include "vec2.h"

namespace rs = std::ranges;
namespace vs = std::views;
using Position = Vec2<std::size_t>;
using Direction = Vec2<int>;

constexpr auto ColumnCount {16uz};
constexpr auto RowCount {10uz};
constexpr Direction DefaultDirection {+1, 0};
constexpr Position DefaultPosition {ColumnCount / 2, RowCount / 2};
constexpr auto SEED {1uz};

struct Snake {
	std::array<Position, ColumnCount*RowCount> body{};
	std::size_t length{};
	constexpr Snake() = default;
	constexpr void init(this Snake &self);
	constexpr int move(this Snake &self, const Direction direction);
};

enum class Event {
	Up,
	Right,
	Down,
	Left
};

struct World {
	Snake snake{};
	Position food{};
	Direction direction{};
	LCG lcg{};
	std::size_t score{};
	bool win{};
	constexpr World() = default;
	constexpr void init(this World &self);
	constexpr void handle(this World &self, const Event ev);
	constexpr bool update(this World &self);
};

constexpr Position spawn_food(Snake &snake, LCG &lcg)
{
	for (;;) {
		Position random_pos {
			lcg()%ColumnCount,
			lcg()%RowCount,
		};

		if (!rs::contains(snake.body | vs::take(snake.length), random_pos)) {
			return random_pos;
		}
	}
}

constexpr void Snake::init(this Snake &self)
{
	self.body[0] = DefaultPosition;
	self.length = 1;
}

constexpr int Snake::move(this Snake &self, const Direction direction)
{
	std::shift_right(self.body.begin(), self.body.end()-1, 1);

	self.body[0].x += direction.x;
	self.body[0].x += ColumnCount;
	self.body[0].x %= ColumnCount;

	self.body[0].y += direction.y;
	self.body[0].y += RowCount;
	self.body[0].y %= RowCount;

	if (rs::contains(self.body | vs::take(self.length) | vs::drop(1), self.body[0])) {
		return -1;
	}

	return 0;
}

constexpr void World::init(this World &self)
{
	self.snake.init();
	self.direction = DefaultDirection;
	self.lcg.init(SEED);
	self.food = spawn_food(self.snake, self.lcg);
	self.score = 0;
	self.win = false;
}

constexpr void World::handle(this World &self, const Event ev)
{
	auto direction {self.direction};

	switch (ev) {
	case Event::Up:
		direction = Direction{0, -1};
		break;
	case Event::Down:
		direction = Direction{0, +1};
		break;
	case Event::Left:
		direction = Direction{-1, 0};
		break;
	case Event::Right:
		direction = Direction{+1, 0};
		break;
	}

	if (direction.x*self.direction.x+direction.y*self.direction.y == 0) {
		self.direction = direction;
	}
}

constexpr bool World::update(this World &self)
{
	const auto lastSegment {self.snake.body[self.snake.length-1]};

	if (self.snake.move(self.direction) < 0) {
		self.init();
		return true;
	}

	if (self.snake.body[0] == self.food) {
		self.snake.body[self.snake.length] = lastSegment;
		self.snake.length += 1;
		if (self.snake.length == ColumnCount*RowCount) {
			self.win = true;
			return false;
		}
		self.score += 1;
		self.food = spawn_food(self.snake, self.lcg);
	}

	return false;
}

#endif
