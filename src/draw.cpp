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

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "draw.h"

constexpr SDL_Color ColorBackground{0xBE, 0xBE, 0xBE, 0xFF};
constexpr SDL_Color ColorBody{0xFF, 0xFF, 0, 0xFF};
constexpr SDL_Color ColorHead{0, 0xFF, 0, 0xFF};
constexpr SDL_Color ColorGrid{0, 0, 0, 0xFF};
constexpr SDL_Color ColorFood{0, 0, 0xFF, 0xFF};
constexpr SDL_Color ColorScore{0, 0, 0, 0xFF};

bool Renderer::set_color(this Renderer &self, SDL_Color c)
{
	return SDL_SetRenderDrawColor(self.ren, c.r, c.g, c.b, c.a);
}

bool Renderer::draw_cell(this Renderer &self, Position pos)
{
	SDL_FRect rect{
		.x = float(pos.x*(Factor+LineWidth)),
		.y = float(pos.y*(Factor+LineWidth)),
		.w = Factor,
		.h = Factor,
	};

	return SDL_RenderFillRect(self.ren, &rect);
}

void Renderer::draw_food(this Renderer &self, Position food)
{
	assert(self.set_color(ColorFood));
	assert(self.draw_cell(food));
}

void Renderer::draw_grid(this Renderer &self)
{
	SDL_FRect rect{};

	assert(self.set_color(ColorGrid));

	for (auto line : vs::iota(ColumnCount*0, ColumnCount-1)) {
		rect.x = line*(Factor+LineWidth)+Factor;
		rect.y = 0.0f;
		rect.w = LineWidth;
		rect.h = GridHeight;
		assert(SDL_RenderFillRect(self.ren, &rect));
	}

	for (auto line : vs::iota(RowCount*0, RowCount)) {
		rect.x = 0.0f;
		rect.y = line*(Factor+LineWidth)+Factor;
		rect.w = GridWidth;
		rect.h = LineWidth;
		assert(SDL_RenderFillRect(self.ren, &rect));
	}
}

void Renderer::draw_snake(this Renderer &self, const Snake &snake)
{
	auto head {snake.body.front()};

	assert(self.set_color(ColorBody));
	for (auto segment : snake.body | vs::take(snake.length) | vs::drop(1))
		assert(self.draw_cell(segment));

	assert(self.set_color(ColorHead));
	assert(self.draw_cell(head));
}

void Renderer::draw_score(this Renderer &self, std::uint64_t score)
{
	SDL_FRect rect{ .x = 0.0f, .y = (Factor+LineWidth)*RowCount, .w = Factor*2, .h = Factor };
	SDL_Surface *surf{};
	SDL_Texture *texture{};

	surf = TTF_RenderText_Solid(self.font, std::format("{:03}", score).c_str(), 0, ColorScore);
	assert(surf);
	texture = SDL_CreateTextureFromSurface(self.ren, surf);
	assert(texture);
	assert(SDL_RenderTexture(self.ren, texture, NULL, &rect));
	SDL_DestroyTexture(texture);
	SDL_DestroySurface(surf);
}

void Renderer::draw(this Renderer &self, const World &w)
{
	assert(self.set_color(ColorBackground));
	assert(SDL_RenderClear(self.ren));

	self.draw_grid();

	self.draw_snake(w.snake);

	self.draw_food(w.food);

	self.draw_score(w.score);

	assert(SDL_RenderPresent(self.ren));
}
