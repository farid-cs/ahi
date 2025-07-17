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

#ifndef AHI_DRAW_H
#define AHI_DRAW_H

#include "world.h"

constexpr auto Factor = 100;

constexpr auto LineWidth = 1;
constexpr auto GridWidth = ColumnCount*Factor + (ColumnCount-1)*LineWidth;
constexpr auto GridHeight = RowCount*Factor + (RowCount-1)*LineWidth;

constexpr auto FontSize = Factor * 0.75;

void draw_world(const World &w);

#endif
