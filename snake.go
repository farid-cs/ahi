package main

import rl "github.com/gen2brain/raylib-go/raylib"

import "math/rand/v2"
import "slices"

type Vec2 struct {
	x int
	y int
}

const (
	FACTOR = 100
	COLUMN_COUNT = 16
	ROW_COUNT = 10
	WINDOW_WIDTH = COLUMN_COUNT * FACTOR
	WINDOW_HEIGHT = ROW_COUNT * FACTOR
	WINDOW_TITLE = "snake"
	FPS = 6
)

var (
	BACKGROUND_COLOR = rl.Gray
	HEAD_COLOR = rl.Green
	TAIL_COLOR = rl.Yellow
	FOOD_COLOR = rl.Blue
	snake []Vec2
	food Vec2
	velocity Vec2
)

func init_state() {
	snake = []Vec2{}
	snake = append(snake, Vec2{7, 4})
	velocity = Vec2{1, 0}
	food = spawn_food()
}

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

func spawn_food() Vec2 {
	for {
		random_pos := Vec2{
			x: rand.IntN(COLUMN_COUNT),
			y: rand.IntN(ROW_COUNT),
		}

		if !slices.Contains(snake, random_pos) {
			return random_pos
		}
	}
}

func update_state() {
	last_segment := snake[len(snake)-1]

	switch rl.GetKeyPressed() {
	case rl.KeyLeft:
		if velocity.x == 0 {
			velocity = Vec2{-1, 0}
		}
	case rl.KeyRight:
		if velocity.x == 0 {
			velocity = Vec2{+1, 0}
		}
	case rl.KeyUp:
		if velocity.y == 0 {
			velocity = Vec2{0, -1}
		}
	case rl.KeyDown:
		if velocity.y == 0 {
			velocity = Vec2{0, +1}
		}
	}

	for i := len(snake)-1; i != 0; i-- {
		snake[i] = snake[i-1]
	}

	snake[0].x += velocity.x
	snake[0].x += COLUMN_COUNT
	snake[0].x %= COLUMN_COUNT

	snake[0].y += velocity.y
	snake[0].y += ROW_COUNT
	snake[0].y %= ROW_COUNT

	for i := 1; i != len(snake); i++ {
		if snake[i] == snake[0] {
			init_state()
			return
		}
	}

	if snake[0] == food {
		snake = append(snake, last_segment)
		food = spawn_food()
	}
}

func main() {
	rl.InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
	defer rl.CloseWindow()

	rl.SetTargetFPS(FPS)

	init_state()

	for !rl.WindowShouldClose() {
		draw_frame()
		update_state()
	}
}
