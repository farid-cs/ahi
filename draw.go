package main

import rl "github.com/gen2brain/raylib-go/raylib"

import "fmt"

const Factor = 100
const LineWidth = 1
const FontSize = Factor * 0.75

var (
	ColorBackground = rl.Gray
	ColorHead       = rl.Green
	ColorTail       = rl.Yellow
	ColorFood       = rl.Blue
	ColorLine       = rl.Black
	ColorScore      = rl.Black
)

func DrawFrame() {
	rl.BeginDrawing()

	rl.ClearBackground(ColorBackground)

	for i := 0; i != ColumnCount; i++ {
		rl.DrawRectangle(int32(i*(Factor+LineWidth)+Factor),
			0, LineWidth, GridHeight, ColorLine)
	}

	for i := 0; i != RowCount; i++ {
		rl.DrawRectangle(0, int32(i*(Factor+LineWidth)+Factor),
			GridWidth, LineWidth, ColorLine)
	}

	for i := 1; i != len(snake); i++ {
		rl.DrawRectangle(int32(snake[i].x*(Factor+LineWidth)),
			int32(snake[i].y*(Factor+LineWidth)), Factor, Factor, ColorTail)
	}

	rl.DrawRectangle(int32(snake[0].x*(Factor+LineWidth)),
		int32(snake[0].y*(Factor+LineWidth)), Factor, Factor, ColorHead)

	rl.DrawCircle(int32(food.x*(Factor+LineWidth)+Factor/2),
		int32(food.y*(Factor+LineWidth)+Factor/2), Factor/2, ColorFood)

	rl.DrawText(fmt.Sprintf("%d", score), 0, GridHeight, FontSize, ColorScore)

	rl.EndDrawing()
}
