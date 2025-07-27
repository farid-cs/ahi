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

#include "raylib.h"

#include "config.h"
#include "draw.h"
#include "event.h"

constexpr auto now {std::chrono::high_resolution_clock::now};

constexpr auto WindowTitle {"ahi " VERSION};
constexpr auto WindowWidth {GridWidth};
constexpr auto WindowHeight {GridHeight + FontSize};

constexpr auto FPS {120};

constexpr std::chrono::milliseconds dt {200};

static std::optional<Event> ev {};
static auto lastUpdateTime {now()};
static World world {};

void setup(void)
{
	InitWindow(WindowWidth, WindowHeight, WindowTitle);

	SetTargetFPS(FPS);

	lastUpdateTime = now();
}

void run(void)
{
	while (!WindowShouldClose() && !world.win) {
		draw_world(world);
		next_event(ev);
		if (now()-lastUpdateTime > dt) {
			if (ev.has_value())
				world.handle(ev.value());
			ev = {};
			world.update();
			lastUpdateTime = now();
		}
	}
}

void cleanup(void)
{
	CloseWindow();
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		if (std::strcmp(argv[1], "-v")) {
			std::println(std::cerr, "{} [-v]", argv[0]);
			return EXIT_FAILURE;
		}
		std::println(std::cerr, "{}", WindowTitle);
		return EXIT_SUCCESS;
	}
	setup();
	run();
	cleanup();
	return EXIT_SUCCESS;
}
