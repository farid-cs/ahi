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

#include <format>
#include <ranges>

#include "raylib.h"

#include "draw.h"

constexpr auto ColorBackground {GRAY};
constexpr auto ColorHead       {GREEN};
constexpr auto ColorTail       {YELLOW};
constexpr auto ColorFood       {BLUE};
constexpr auto ColorLine       {BLACK};
constexpr auto ColorScore      {BLACK};

static void draw_food(const Position &food)
{
	auto x {food.x*(Factor+LineWidth)+Factor/2};
	auto y {food.y*(Factor+LineWidth)+Factor/2};

	DrawCircle(x, y, Factor/2, ColorFood);
}

static void draw_grid()
{
	int x{}, y{};

	for (auto line : vs::iota(0uz, ColumnCount)) {
		x = line*(Factor+LineWidth)+Factor;
		y = 0;
		DrawRectangle(x, y, LineWidth, GridHeight, ColorLine);
	}

	for (auto line : vs::iota(0uz, RowCount)) {
		x = 0;
		y = line*(Factor+LineWidth)+Factor;
		DrawRectangle(x, y, GridWidth, LineWidth, ColorLine);
	}
}

static void draw_snake(const Snake &snake)
{
	const auto &head = snake.body.front();
	int x{}, y{};

	for (const auto &segment : snake.body | vs::take(snake.length) | vs::drop(1)) {
		x = segment.x*(Factor+LineWidth);
		y = segment.y*(Factor+LineWidth);
		DrawRectangle(x, y, Factor, Factor, ColorTail);
	}

	x = head.x*(Factor+LineWidth);
	y = head.y*(Factor+LineWidth);
	DrawRectangle(x, y, Factor, Factor, ColorHead);
}

static void draw_score(int score)
{
	DrawText(std::format("{}", score).c_str(), 0, GridHeight, FontSize, ColorScore);
}

void draw_world(const World &w)
{
	BeginDrawing();

	ClearBackground(ColorBackground);

	draw_grid();

	draw_snake(w.snake);

	draw_food(w.food);

	draw_score(w.score);

	EndDrawing();
}
