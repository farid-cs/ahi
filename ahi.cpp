#include <format>
#include <cstdlib>
#include <cstring>
#include <print>
#include <iostream>

#include "raylib.h"

#include "draw.h"
#include "event.h"

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

	if (argc > 1 && !std::strcmp(argv[1], "-v")) {
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
