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
#include <cassert>
#include <ranges>

#include "vec2.h"
#include "config.h"

namespace rs = std::ranges;
namespace vs = std::views;

enum class Event {
	Up,
	Right,
	Down,
	Left
};

struct Snake {
	std::array<Position, ColumnCount*RowCount> body{};
	size_t length{};
	constexpr Snake();
	constexpr int move(this Snake &self, const Direction direction);
};

struct World {
	Snake snake{};
	Position food{};
	Direction direction{};
	uint64_t score{};
	bool win{};
	constexpr World();
	constexpr World& operator=(const World&) = default;
	constexpr void handle(this World &self, const Event ev);
	constexpr void update(this World &self);
};

constexpr Position spawn_food(Snake &snake);

constexpr Snake::Snake()
{
	constexpr Position DefaultHeadPosition{ColumnCount / 2, RowCount / 2};
	Snake &self {*this};

	self.body[0] = DefaultHeadPosition;
	self.length = 1;
}

constexpr World::World()
{
	constexpr Direction DefaultHeadDirection{+1, 0};
	World &self {*this};

	self.food = spawn_food(self.snake);
	self.direction = DefaultHeadDirection;
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

constexpr void World::update(this World &self)
{
	const auto last_segment {self.snake.body[self.snake.length-1]};

	if (self.snake.move(self.direction) < 0) {
		self = World{};
		return;
	}

	if (self.snake.body[0] == self.food) {
		self.snake.body[self.snake.length] = last_segment;
		self.snake.length += 1;
		if (self.snake.length == ColumnCount*RowCount) {
			self.win = true;
			return;
		}
		self.score += 1;
		self.food = spawn_food(self.snake);
	}
}

constexpr Position spawn_food(Snake &snake)
{
	uint64_t x{}, y{};

	for (x = 0; x != ColumnCount; x++) {
		for (y = 0; y != RowCount; y++) {
			Position pos{x, y};

			if (!rs::contains(snake.body | vs::take(snake.length), pos)) {
				return pos;
			}
		}
	}
	std::unreachable();
}

#endif
