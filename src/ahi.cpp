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

#include <cstdlib>
#include <cstring>
#include <print>
#include <iostream>

#include "raylib.h"

#include "draw.h"
#include "event.h"
#include "config.h"

constexpr auto WindowTitle = "ahi " VERSION;
constexpr auto WindowWidth = GridWidth;
constexpr auto WindowHeight = GridHeight + FontSize;

constexpr auto FPS = 120;

constexpr auto dt = 1.0 / 5.0;

int main(int argc, char *argv[]) {
	Controller con;
	Event ev;
	double lastUpdateTime;
	World world;

	if (argc > 1) {
		if (std::strcmp(argv[1], "-v")) {
			std::println(std::cerr, "{} [-v]", argv[0]);
			return EXIT_FAILURE;
		}
		std::println(std::cerr, "{}", WindowTitle);
		return EXIT_SUCCESS;
	}

	InitWindow(WindowWidth, WindowHeight, WindowTitle);

	SetTargetFPS(FPS);

	world.Init();
	lastUpdateTime = GetTime();

	while(!WindowShouldClose() && !world.win) {
		DrawWorld(world);
		ev = con.NextEvent();
		if (GetTime()-lastUpdateTime > dt) {
			world.Update(ev);
			lastUpdateTime = GetTime();
		}
	}

	CloseWindow();
	return EXIT_SUCCESS;
}
