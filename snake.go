package main

import rl "github.com/gen2brain/raylib-go/raylib"

import "math/rand/v2"
import "image/color"

const (
	COLUMN_COUNT = 16
	ROW_COUNT = 10
	WINDOW_WIDTH = COLUMN_COUNT * 100
	WINDOW_HEIGHT = ROW_COUNT * 100
)

var (
	CELL_COLOR = rl.Gray
	HEAD_COLOR = rl.Green
	FOOD_COLOR = rl.Blue
	snake_head, food struct {
		row int
		col int
	}
	velocity struct {
		x int
		y int
	}
	grid [ROW_COUNT][COLUMN_COUNT] color.RGBA
)

func init() {
	snake_head.row = 4
	snake_head.col = 7
	velocity.x = 1
	food.row = rand.IntN(ROW_COUNT)
	food.col = rand.IntN(COLUMN_COUNT)
	for i := range grid {
		for j := range grid[0] {
			grid[i][j] = rl.Gray
		}
	}
}

func main() {
	rl.InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "snake")
	defer rl.CloseWindow()

	rl.SetTargetFPS(4)

	for !rl.WindowShouldClose() {
		rl.BeginDrawing()

		rl.ClearBackground(rl.Red)

		/* display the grid */
		for i := range grid {
			for j := range grid[0] {
				rl.DrawRectangle(
					int32(j * 100 + 2),
					int32(i * 100 + 2),
					96,
					96,
					grid[i][j],
				)
			}
		}

		rl.DrawCircle(int32(food.col * 100 + 50), int32(food.row * 100 + 50), 48.0, FOOD_COLOR);

		rl.EndDrawing()

		/* handle input */
		switch rl.GetKeyPressed() {
		case rl.KeyUp:
			if velocity.y != 0 {
				break
			}
			velocity.x = 0
			velocity.y = -1
		case rl.KeyDown:
			if velocity.y != 0 {
				break
			}
			velocity.x = 0
			velocity.y = +1
		case rl.KeyLeft:
			if velocity.x != 0 {
				break
			}
			velocity.x = -1
			velocity.y = 0
		case rl.KeyRight:
			if velocity.x != 0 {
				break
			}
			velocity.x = +1
			velocity.y = 0
		}

		/* update state */
		grid[snake_head.row][snake_head.col] = CELL_COLOR

		snake_head.col += velocity.x
		snake_head.col += COLUMN_COUNT
		snake_head.col %= COLUMN_COUNT
		snake_head.row += velocity.y
		snake_head.row += ROW_COUNT
		snake_head.row %= ROW_COUNT

		grid[snake_head.row][snake_head.col] = HEAD_COLOR

		if snake_head == food {
			food.row = rand.IntN(ROW_COUNT)
			food.col = rand.IntN(COLUMN_COUNT)
		}
	}
}
