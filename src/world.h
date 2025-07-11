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
#include <cstddef>
#include <array>
#include <random>
#include <ranges>

#include "vec2.h"
#include "lcg.h"

namespace rs = std::ranges;
namespace vs = std::views;
using Position = Vec2<std::size_t>;
using Direction = Vec2<int>;

constexpr std::size_t ColumnCount {16};
constexpr std::size_t RowCount {10};
constexpr Direction DefaultDirection {+1, 0};
constexpr Position DefaultPosition {ColumnCount / 2, RowCount / 2};
constexpr std::size_t SEED {1};

struct Snake {
	std::array<Position, ColumnCount*RowCount> body;
	std::size_t length;
	constexpr Snake() : body{}, length{} {}
	constexpr void Init();
	constexpr int Move(const Direction direction);
};

enum class Event {
	None,
	Up,
	Right,
	Down,
	Left
};

struct World {
	Snake snake;
	Position food;
	Direction direction;
	LCG lcg;
	std::size_t score;
	bool win;
	constexpr World() : score{}, win{} {}
	constexpr void Init();
	constexpr void Update(const Event ev);
};

constexpr Position spawnFood(Snake &snake, LCG &lcg)
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

constexpr void Snake::Init()
{
	Snake &self {*this};

	self.body[0] = DefaultPosition;
	self.length = 1;
}

constexpr int Snake::Move(const Direction direction)
{
	Snake &self {*this};

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

constexpr void World::Init()
{
	World &self {*this};

	self.snake.Init();
	self.direction = DefaultDirection;
	self.lcg.Init(SEED);
	self.food = spawnFood(self.snake, self.lcg);
	self.score = 0;
	self.win = false;
}

constexpr void World::Update(const Event ev)
{
	World &self {*this};
	const auto lastSegment {self.snake.body[self.snake.length-1]};
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
	case Event::None:
		break;
	}

	if (direction.x*self.direction.x+direction.y*self.direction.y == 0) {
		self.direction = direction;
	}

	if (self.snake.Move(self.direction) < 0) {
		self.Init();
		return;
	}

	if (self.snake.body[0].x == self.food.x && self.snake.body[0].y == self.food.y) {
		self.snake.body[self.snake.length] = lastSegment;
		self.snake.length += 1;
		if (self.snake.length == ColumnCount*RowCount) {
			self.win = true;
			return;
		}
		self.score += 1;
		self.food = spawnFood(self.snake, self.lcg);
	}
}

#endif
