#include <format>
#include <ranges>

#include "raylib.h"

#include "draw.h"

constexpr auto ColorBackground {GRAY};
constexpr auto ColorHead       {GREEN};
constexpr auto ColorTail       {YELLOW};
constexpr auto ColorFood       {BLUE};
constexpr auto ColorLine       {BLACK};
constexpr auto ColorScore      {BLACK};

static void DrawFood(const Position &food)
{
	DrawCircle(food.x*(Factor+LineWidth)+Factor/2,
		food.y*(Factor+LineWidth)+Factor/2, Factor/2, ColorFood);
}

static void DrawGrid()
{
	for (auto line : vs::iota(size_t(0), ColumnCount))
		DrawRectangle(line*(Factor+LineWidth)+Factor,
			0, LineWidth, GridHeight, ColorLine);

	for (auto line : vs::iota(size_t(0), RowCount))
		DrawRectangle(0, line*(Factor+LineWidth)+Factor,
			GridWidth, LineWidth, ColorLine);
}

static void DrawSnake(const Snake &snake)
{
	const auto &head = snake.body.front();

	for (const auto &segment : snake.body | vs::take(snake.length) | vs::drop(1))
		DrawRectangle(segment.x*(Factor+LineWidth),
			segment.y*(Factor+LineWidth), Factor, Factor, ColorTail);

	DrawRectangle(head.x*(Factor+LineWidth),
		head.y*(Factor+LineWidth), Factor, Factor, ColorHead);
}

static void DrawScore(int score)
{
	DrawText(std::format("{}", score).c_str(), 0, GridHeight, FontSize, ColorScore);
}

void DrawWorld(const World &w)
{
	BeginDrawing();

	ClearBackground(ColorBackground);

	DrawGrid();

	DrawSnake(w.snake);

	DrawFood(w.food);

	DrawScore(w.score);

	EndDrawing();
}
