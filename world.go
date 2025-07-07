package main

import "math/rand/v2"
import "slices"

const (
	ColumnCount = 16
	RowCount    = 10
)

type Vec2 struct {
	x int
	y int
}

type Snake []Vec2

type World struct {
	snake          Snake
	food           Vec2
	velocity       Vec2
	score          int
	win            bool
}

const (
	EventNone = iota
	EventUp
	EventRight
	EventDown
	EventLeft
)

var DefaultVelocity = Vec2{+1, 0}
var DefaultPosition = Vec2{ColumnCount / 2, RowCount / 2}

func spawnFood(snake Snake) Vec2 {
	if len(snake) >= RowCount*ColumnCount {
		panic("nowhere to place food")
	}
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

func (self Snake) Move(velocity Vec2) int {
	for i := len(self) - 1; i != 0; i-- {
		self[i] = self[i-1]
	}

	self[0].x += velocity.x
	self[0].x += ColumnCount
	self[0].x %= ColumnCount

	self[0].y += velocity.y
	self[0].y += RowCount
	self[0].y %= RowCount

	for i := 1; i != len(self); i++ {
		if self[i] == self[0] {
			return -1
		}
	}

	return 0
}

func (self *World) Init() {
	self.snake = Snake{}
	self.snake = append(self.snake, DefaultPosition)
	self.velocity = DefaultVelocity
	self.food = spawnFood(self.snake)
	self.score = 0
}

func (self *World) Update(ev int) {
	lastSegment := self.snake[len(self.snake)-1]
	velocity := self.velocity

	switch ev {
	case EventUp:
		velocity = Vec2{0, -1}
	case EventDown:
		velocity = Vec2{0, +1}
	case EventLeft:
		velocity = Vec2{-1, 0}
	case EventRight:
		velocity = Vec2{+1, 0}
	}

	if velocity.x*self.velocity.x+velocity.y*self.velocity.y == 0 {
		self.velocity = velocity
	}

	if self.snake.Move(self.velocity) < 0 {
		self.Init()
		return
	}

	if self.snake[0] == self.food {
		self.snake = append(self.snake, lastSegment)
		if len(self.snake) == ColumnCount*RowCount {
			self.win = true
			return
		}
		self.score += 1
		self.food = spawnFood(self.snake)
	}
}
