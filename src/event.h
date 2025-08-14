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

#ifndef AHI_EVENT_H
#define AHI_EVENT_H

#include <queue>

#include "world.h"

class EventListener {
	std::queue<Event> events{};
public:
	EventListener() = default;
	bool listen(this EventListener &);
	void handle(this EventListener &, World &);
};

#endif
