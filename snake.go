package main

import rl "github.com/gen2brain/raylib-go/raylib"

import "math/rand/v2"

const (
	COLUMN_COUNT = 16
	ROW_COUNT = 10
	WINDOW_WIDTH = COLUMN_COUNT * 100
	WINDOW_HEIGHT = ROW_COUNT * 100
)

type Position struct {
	row int
	col int
}

var (
	BACKGROUND_COLOR = rl.Gray
	HEAD_COLOR = rl.Green
	TAIL_COLOR = rl.Yellow
	FOOD_COLOR = rl.Blue
	snake []Position
	food Position
	velocity struct {
		x int
		y int
	}
)

func init() {
	snake = append(snake, Position{row: 4, col: 7})
	velocity.x = 1
	food.row = rand.IntN(ROW_COUNT)
	food.col = rand.IntN(COLUMN_COUNT)
}

func main() {
	rl.InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "snake")
	defer rl.CloseWindow()

	rl.SetTargetFPS(6)

	for !rl.WindowShouldClose() {
		rl.BeginDrawing()

		rl.ClearBackground(BACKGROUND_COLOR)

		for i := 1; i != len(snake); i++ {
			rl.DrawRectangle(int32(snake[i].col * 100),
				int32(snake[i].row * 100), 100, 100, TAIL_COLOR)
		}

		rl.DrawRectangle(int32(snake[0].col * 100),
			int32(snake[0].row * 100), 100, 100, HEAD_COLOR)

		rl.DrawCircle(int32(food.col * 100 + 50),
			int32(food.row * 100 + 50), 50.0, FOOD_COLOR)

		rl.EndDrawing()

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

		last_segment := snake[len(snake)-1]
		for i := len(snake)-1; i != 0; i-- {
			snake[i] = snake[i-1]
		}

		snake[0].col += velocity.x
		snake[0].col += COLUMN_COUNT
		snake[0].col %= COLUMN_COUNT

		snake[0].row += velocity.y
		snake[0].row += ROW_COUNT
		snake[0].row %= ROW_COUNT

		if snake[0] == food {
			snake = append(snake, last_segment)
			food.row = rand.IntN(ROW_COUNT)
			food.col = rand.IntN(COLUMN_COUNT)
		}
	}
}
