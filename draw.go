package main

import rl "github.com/gen2brain/raylib-go/raylib"

import "fmt"

const FACTOR = 100
const LINE_WIDTH = 1
const FONT_SIZE = FACTOR * 0.75

var (
	BACKGROUND_COLOR = rl.Gray
	HEAD_COLOR       = rl.Green
	TAIL_COLOR       = rl.Yellow
	FOOD_COLOR       = rl.Blue
	LINE_COLOR       = rl.Black
	SCORE_COLOR      = rl.Black
)

func draw_frame() {
	rl.BeginDrawing()

	rl.ClearBackground(BACKGROUND_COLOR)

	for i := 0; i != COLUMN_COUNT; i++ {
		rl.DrawRectangle(int32(i*(FACTOR+LINE_WIDTH)+FACTOR),
			0, LINE_WIDTH, GRID_HEIGHT, LINE_COLOR)
	}

	for i := 0; i != ROW_COUNT; i++ {
		rl.DrawRectangle(0, int32(i*(FACTOR+LINE_WIDTH)+FACTOR),
			GRID_WIDTH, LINE_WIDTH, LINE_COLOR)
	}

	for i := 1; i != len(snake); i++ {
		rl.DrawRectangle(int32(snake[i].x*(FACTOR+LINE_WIDTH)),
			int32(snake[i].y*(FACTOR+LINE_WIDTH)), FACTOR, FACTOR, TAIL_COLOR)
	}

	rl.DrawRectangle(int32(snake[0].x*(FACTOR+LINE_WIDTH)),
		int32(snake[0].y*(FACTOR+LINE_WIDTH)), FACTOR, FACTOR, HEAD_COLOR)

	rl.DrawCircle(int32(food.x*(FACTOR+LINE_WIDTH)+FACTOR/2),
		int32(food.y*(FACTOR+LINE_WIDTH)+FACTOR/2), FACTOR/2, FOOD_COLOR)

	rl.DrawText(fmt.Sprintf("%d", score), 0, GRID_HEIGHT, FONT_SIZE, SCORE_COLOR)

	rl.EndDrawing()
}
