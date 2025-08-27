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

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <print>
#include <thread>

#include "version.h"
#include "draw.h"
#include "event.h"

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
using Milliseconds = std::chrono::milliseconds;
using std::this_thread::sleep_until;

constexpr auto now {std::chrono::high_resolution_clock::now};

constexpr auto WindowTitle {"ahi " VERSION};
constexpr auto WindowWidth {GridWidth};
constexpr auto WindowHeight {GridHeight + ScoreHeight};

constexpr Milliseconds MIN_STATE_DURATION{200};
constexpr Milliseconds MIN_FRAME_DURATION{1};

int main(int argc, char *argv[])
{
	EventListener el{};
	TimePoint lastUpdateTime{};
	TimePoint frameUpdateTime{};
	World world{};
	SDL_Window *window{};
	DrawingContext dc{};

	if (argc > 1) {
		if (std::strcmp(argv[1], "-v")) {
			std::println(std::cerr, "{} [-v]", argv[0]);
			return EXIT_FAILURE;
		}
		std::println(std::cerr, "{}", WindowTitle);
		return EXIT_SUCCESS;
	}

	/* setup */
	assert(SDL_Init(0));
	assert(TTF_Init());
	window = SDL_CreateWindow(WindowTitle, WindowWidth, WindowHeight, 0);
	assert(window);
	dc.init(window);
	lastUpdateTime = now();

	/* run */
	while (el.listen() && !world.win) {
		draw(dc, world);
		frameUpdateTime = now();
		if (now() - lastUpdateTime > MIN_STATE_DURATION) {
			el.handle(world);
			world.update();
			lastUpdateTime = now();
		}
		sleep_until(frameUpdateTime+MIN_FRAME_DURATION);
	}

	/* cleanup */
	dc.deinit();
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}
