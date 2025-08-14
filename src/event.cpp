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

#include "SDL3/SDL.h"

#include "event.h"

bool EventListener::listen(this EventListener &self)
{
	SDL_Event e{};

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}
		if (e.type == SDL_EVENT_KEY_DOWN) {
			switch (e.key.key) {
			case SDLK_UP:
				self.events.push(Event::Up);
				break;
			case SDLK_DOWN:
				self.events.push(Event::Down);
				break;
			case SDLK_LEFT:
				self.events.push(Event::Left);
				break;
			case SDLK_RIGHT:
				self.events.push(Event::Right);
				break;
			default: 
				continue;
			}
			if (self.events.size() > 100uz)
				self.events.pop();
		}
	}
	return true;
}

void EventListener::handle(this EventListener &self, World &w)
{
	if (self.events.empty())
		return;
	w.handle(self.events.front());
	self.events.pop();
}
