#ifndef AHI_DRAW_H
#define AHI_DRAW_H

#include "world.h"

constexpr auto Factor = 100;

constexpr auto LineWidth = 1;
constexpr auto GridWidth = ColumnCount*Factor + (ColumnCount-1)*LineWidth;
constexpr auto GridHeight = RowCount*Factor + (RowCount-1)*LineWidth;

constexpr auto FontSize = Factor * 0.75;

void DrawWorld(World &w);

#endif
