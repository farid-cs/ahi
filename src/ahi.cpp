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

#include "SDL3/SDL.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "config.h"
#include "draw.h"
#include "event.h"

constexpr auto now {std::chrono::high_resolution_clock::now};

constexpr auto WindowTitle {"ahi " VERSION};
constexpr auto WindowWidth {GridWidth};
constexpr auto WindowHeight {GridHeight + Factor};

constexpr std::chrono::milliseconds MIN_STATE_DURATION{200};
constexpr std::chrono::milliseconds MIN_FRAME_DURATION{1};

static std::queue<Event> ev{};
static auto lastUpdateTime {now()};
static auto frameUpdateTime {now()};
static World world {};

static SDL_Window *window{};
static Renderer renderer{};

static void setup(void)
{
	assert(SDL_Init(0));
	assert(TTF_Init());
	window = SDL_CreateWindow(WindowTitle, WindowWidth, WindowHeight, 0);
	assert(window);
	renderer.ren = SDL_CreateRenderer(window, nullptr);
	assert(renderer.ren);
	renderer.font = TTF_OpenFont("res/font.ttf", 32.f);
	assert(renderer.font);
	lastUpdateTime = now();
}

static void run(void)
{
	while (next_event(ev)) {
		renderer.draw(world);
		frameUpdateTime = now();
		if (now() - lastUpdateTime > MIN_STATE_DURATION) {
			if (!ev.empty()) {
				if (ev.size() > 100uz)
					for (auto i{0uz}; i != ev.size()-100uz; i++)
						ev.pop();
				world.handle(ev.front());
				ev.pop();
			}
			world.update();
			lastUpdateTime = now();
		}
		std::this_thread::sleep_until(frameUpdateTime+MIN_FRAME_DURATION);
	}
}

static void cleanup(void)
{
	SDL_DestroyRenderer(renderer.ren);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

int main(int argc, char *argv[])
{
	if (argc > 1) {
		if (!std::strcmp(argv[0], "-v")) {
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
