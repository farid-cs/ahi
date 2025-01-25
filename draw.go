package main

import rl "github.com/gen2brain/raylib-go/raylib"

const FACTOR = 100

var (
	BACKGROUND_COLOR = rl.Gray
	HEAD_COLOR = rl.Green
	TAIL_COLOR = rl.Yellow
	FOOD_COLOR = rl.Blue
)

func draw_frame() {
	rl.BeginDrawing()

	rl.ClearBackground(BACKGROUND_COLOR)

	for i := 1; i != len(snake); i++ {
		rl.DrawRectangle(int32(snake[i].x * FACTOR),
			int32(snake[i].y * FACTOR), FACTOR, FACTOR, TAIL_COLOR)
	}

	rl.DrawRectangle(int32(snake[0].x * FACTOR),
		int32(snake[0].y * FACTOR), FACTOR, FACTOR, HEAD_COLOR)

	rl.DrawCircle(int32(food.x * FACTOR + FACTOR / 2),
		int32(food.y * FACTOR + FACTOR / 2), FACTOR / 2, FOOD_COLOR)

	rl.EndDrawing()
}
