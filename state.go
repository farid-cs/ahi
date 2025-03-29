package main

import rl "github.com/gen2brain/raylib-go/raylib"
import "math/rand/v2"
import "slices"

const COLUMN_COUNT = 16
const ROW_COUNT = 10

type Vec2 struct {
	x int
	y int
}

var (
	snake []Vec2
	food Vec2
	velocity Vec2
	win bool
	score int
)

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

func init_state() {
	snake = []Vec2{}
	snake = append(snake, Vec2{COLUMN_COUNT/2, ROW_COUNT/2})
	velocity = Vec2{1, 0}
	food = spawn_food()
	score = 0
}

func update_state() {
	last_segment := snake[len(snake)-1]

	switch rl.GetKeyPressed() {
	case rl.KeyUp:
		if velocity.y == 0 {
			velocity = Vec2{0, -1}
		}
	case rl.KeyDown:
		if velocity.y == 0 {
			velocity = Vec2{0, +1}
		}
	case rl.KeyLeft:
		if velocity.x == 0 {
			velocity = Vec2{-1, 0}
		}
	case rl.KeyRight:
		if velocity.x == 0 {
			velocity = Vec2{+1, 0}
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
		if len(snake) == COLUMN_COUNT * ROW_COUNT {
			win = true
			return
		}
		score += 1
		food = spawn_food()
	}
}
