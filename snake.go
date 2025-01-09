package main

import rl "github.com/gen2brain/raylib-go/raylib"

import "math/rand/v2"

type Vec2 struct {
	x int
	y int
}

const (
	COLUMN_COUNT = 16
	ROW_COUNT = 10
	WINDOW_WIDTH = COLUMN_COUNT * 100
	WINDOW_HEIGHT = ROW_COUNT * 100
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

func main() {
	rl.InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "snake")
	defer rl.CloseWindow()

	rl.SetTargetFPS(6)

	init_state()

	for !rl.WindowShouldClose() {
		draw_frame()
		update_state()
	}
}

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
		rl.DrawRectangle(int32(snake[i].x * 100),
			int32(snake[i].y * 100), 100, 100, TAIL_COLOR)
	}

	rl.DrawRectangle(int32(snake[0].x * 100),
		int32(snake[0].y * 100), 100, 100, HEAD_COLOR)

	rl.DrawCircle(int32(food.x * 100 + 50),
		int32(food.y * 100 + 50), 50.0, FOOD_COLOR)

	rl.EndDrawing()
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

func spawn_food() Vec2 {
GENERATE:
	random_pos := Vec2{
		x: rand.IntN(COLUMN_COUNT),
		y: rand.IntN(ROW_COUNT),
	}

	for i := range snake {
		if random_pos == snake[i] {
			goto GENERATE
		}
	}

	return random_pos
}
