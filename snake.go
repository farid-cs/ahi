package main

import rl "github.com/gen2brain/raylib-go/raylib"

const (
	EMPTY = 0
	HEAD = 1
	WIDTH = 16
	HEIGHT = 10
	WINDOW_WIDTH = int32(100 * WIDTH)
	WINDOW_HEIGHT = int32(100 * HEIGHT)
)

var (
	snake_head struct {
		row int
		col int
	}
	velocity struct {
		x int
		y int
	}
	grid = [HEIGHT][WIDTH]int{}
)

func init() {
	snake_head.row = 4
	snake_head.col = 7
	velocity.x = 1
	grid[snake_head.row][snake_head.col] = HEAD
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
				var color = rl.Gray

				if grid[i][j] == HEAD {
					color = rl.Green
				}

				rl.DrawRectangle(
					int32(j * 100 + 2),
					int32(i * 100 + 2),
					96,
					96,
					color,
				)
			}
		}

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
		grid[snake_head.row][snake_head.col] = EMPTY

		snake_head.col += velocity.x
		snake_head.col %= WIDTH
		snake_head.row += velocity.y
		snake_head.row %= HEIGHT
		if snake_head.row < 0 {
			snake_head.row = HEIGHT - 1
		}
		if snake_head.col < 0 {
			snake_head.col = WIDTH - 1
		}

		grid[snake_head.row][snake_head.col] = HEAD
	}
}
