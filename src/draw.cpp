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

#include <cassert>
#include <format>
#include <ranges>

#include "sdl.h"

#include "draw.h"

struct Color {
	std::uint8_t r{};
	std::uint8_t g{};
	std::uint8_t b{};
	std::uint8_t a{};
	constexpr Color(const char *s)
	{
		constexpr auto hex = [](char ch)
		{
			return ch > 'A' ? ch-'A'+10 : ch-'0';
		};

		assert(s[0] == '#');
		assert(s[1] >= '0' && s[1] <= 'F');
		assert(s[2] >= '0' && s[2] <= 'F');
		assert(s[3] >= '0' && s[3] <= 'F');
		assert(s[4] >= '0' && s[4] <= 'F');
		assert(s[5] >= '0' && s[5] <= 'F');
		assert(s[6] >= '0' && s[6] <= 'F');
		assert(s[7] >= '0' && s[7] <= 'F');
		assert(s[8] >= '0' && s[8] <= 'F');
		assert(!s[9]);

		this->r = hex(s[1])*16 + hex(s[2]);
		this->g = hex(s[3])*16 + hex(s[4]);
		this->b = hex(s[5])*16 + hex(s[6]);
		this->a = hex(s[7])*16 + hex(s[8]);
	}
	constexpr SDL_Color sdl_color(this const Color &self)
	{
		return SDL_Color{
			.r = self.r,
			.g = self.g,
			.b = self.b,
			.a = self.a,
		};
	}
};

constexpr Color ColorBackground = "#BEBEBEFF";
constexpr Color ColorBody = "#FFFF00FF";
constexpr Color ColorHead = "#00FF00FF";
constexpr Color ColorGrid = "#000000FF";
constexpr Color ColorFood = "#0000FFFF";
constexpr Color ColorScore = "#000000FF";

bool set_color(Color c)
{
	return SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

bool draw_cell(Position pos)
{
	SDL_FRect rect{
		.x = float(pos.x*(Factor+LineWidth)),
		.y = float(pos.y*(Factor+LineWidth)),
		.w = Factor,
		.h = Factor,
	};

	return SDL_RenderFillRect(renderer, &rect);
}

void draw_food(Position food)
{
	assert(set_color(ColorFood));
	assert(draw_cell(food));
}

void draw_grid()
{
	SDL_FRect rect{};

	assert(set_color(ColorGrid));

	for (auto line : vs::iota(std::uint64_t{}, ColumnCount-std::uint64_t{1})) {
		rect.x = line*(Factor+LineWidth)+Factor;
		rect.y = 0.0f;
		rect.w = LineWidth;
		rect.h = GridHeight;
		assert(SDL_RenderFillRect(renderer, &rect));
	}

	for (auto line : vs::iota(std::uint64_t{}, RowCount)) {
		rect.x = 0.0f;
		rect.y = line*(Factor+LineWidth)+Factor;
		rect.w = GridWidth;
		rect.h = LineWidth;
		assert(SDL_RenderFillRect(renderer, &rect));
	}
}

void draw_snake(const Snake &snake)
{
	auto head {snake.body.front()};

	assert(set_color(ColorBody));
	for (auto segment : snake.body | vs::take(snake.length) | vs::drop(1))
		assert(draw_cell(segment));

	assert(set_color(ColorHead));
	assert(draw_cell(head));
}

void draw_score(std::uint64_t score)
{
	SDL_FRect rect{
		.x = 0.0f,
		.y = (Factor+LineWidth)*RowCount,
		.w = ScoreWidth,
		.h = ScoreHeight,
	};
	SDL_Surface *surface{};
	SDL_Texture *texture{};

	surface = TTF_RenderText_Solid(font, std::format("{:03}", score).c_str(), 0, ColorScore.sdl_color());
	assert(surface);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	assert(texture);
	assert(SDL_RenderTexture(renderer, texture, NULL, &rect));
	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surface);
}

void draw(const World &w)
{
	assert(set_color(ColorBackground));
	assert(SDL_RenderClear(renderer));

	draw_grid();

	draw_snake(w.snake);

	draw_food(w.food);

	draw_score(w.score);

	assert(SDL_RenderPresent(renderer));
}
