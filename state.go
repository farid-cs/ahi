package main

import rl "github.com/gen2brain/raylib-go/raylib"
import "math/rand/v2"
import "slices"

const ColumnCount = 16
const RowCount = 10

type Vec2 struct {
	x int
	y int
}

var (
	snake    []Vec2
	food     Vec2
	velocity Vec2
	win      bool
	score    int
)

func spawnFood() Vec2 {
	for {
		random_pos := Vec2{
			x: rand.IntN(ColumnCount),
			y: rand.IntN(RowCount),
		}

		if !slices.Contains(snake, random_pos) {
			return random_pos
		}
	}
}

func InitState() {
	snake = []Vec2{}
	snake = append(snake, Vec2{ColumnCount / 2, RowCount / 2})
	velocity = Vec2{1, 0}
	food = spawnFood()
	score = 0
}

func UpdateState() {
	lastSegment := snake[len(snake)-1]

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

	for i := len(snake) - 1; i != 0; i-- {
		snake[i] = snake[i-1]
	}

	snake[0].x += velocity.x
	snake[0].x += ColumnCount
	snake[0].x %= ColumnCount

	snake[0].y += velocity.y
	snake[0].y += RowCount
	snake[0].y %= RowCount

	for i := 1; i != len(snake); i++ {
		if snake[i] == snake[0] {
			InitState()
			return
		}
	}

	if snake[0] == food {
		snake = append(snake, lastSegment)
		if len(snake) == ColumnCount*RowCount {
			win = true
			return
		}
		score += 1
		food = spawnFood()
	}
}
