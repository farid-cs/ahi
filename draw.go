package main

import rl "github.com/gen2brain/raylib-go/raylib"

const FACTOR = 100
const GRID_WIDTH = 1

var (
	BACKGROUND_COLOR = rl.Gray
	HEAD_COLOR = rl.Green
	TAIL_COLOR = rl.Yellow
	FOOD_COLOR = rl.Blue
)

func draw_frame() {
	rl.BeginDrawing()

	rl.ClearBackground(BACKGROUND_COLOR)

	for i := 0; i != COLUMN_COUNT; i++ {
		rl.DrawRectangle(int32(i * (FACTOR + GRID_WIDTH) + FACTOR),
			0, GRID_WIDTH, WINDOW_HEIGHT, rl.Black)
	}

	for i := 0; i != ROW_COUNT; i++ {
		rl.DrawRectangle(0, int32(i * (FACTOR + GRID_WIDTH) + FACTOR),
		WINDOW_WIDTH, GRID_WIDTH, rl.Black)
	}

	for i := 1; i != len(snake); i++ {
		rl.DrawRectangle(int32(snake[i].x * (FACTOR + GRID_WIDTH)),
			int32(snake[i].y * (FACTOR + GRID_WIDTH)), FACTOR, FACTOR, TAIL_COLOR)
	}

	rl.DrawRectangle(int32(snake[0].x * (FACTOR + GRID_WIDTH)),
		int32(snake[0].y * (FACTOR + GRID_WIDTH)), FACTOR, FACTOR, HEAD_COLOR)

	rl.DrawCircle(int32(food.x * (FACTOR + GRID_WIDTH) + FACTOR / 2),
		int32(food.y * (FACTOR + GRID_WIDTH) + FACTOR / 2), FACTOR / 2, FOOD_COLOR)

	rl.EndDrawing()
}
