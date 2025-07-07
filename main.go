package main

import rl "github.com/gen2brain/raylib-go/raylib"

import "fmt"
import "math/rand/v2"
import "os"
import "slices"

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

type Controller struct {
	event int
}

const (
	Version = "0.2"

	ColumnCount = 16
	RowCount    = 10
	Factor      = 100

	GridWidth  = ColumnCount*Factor + (ColumnCount-1)*LineWidth
	GridHeight = RowCount*Factor + (RowCount-1)*LineWidth

	WindowTitle  = "ahi " + Version
	WindowWidth  = GridWidth
	WindowHeight = GridHeight + FontSize

	LineWidth = 1
	FontSize  = Factor * 0.75

	FPS = 120

	dt = 1.0 / 5.0
)

const (
	EventNone = iota
	EventUp
	EventRight
	EventDown
	EventLeft
)

var (
	ColorBackground = rl.Gray
	ColorHead       = rl.Green
	ColorTail       = rl.Yellow
	ColorFood       = rl.Blue
	ColorLine       = rl.Black
	ColorScore      = rl.Black
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

func (self *Controller) NextEvent() int {
	switch rl.GetKeyPressed() {
	case rl.KeyUp:
		self.event = EventUp
	case rl.KeyDown:
		self.event = EventDown
	case rl.KeyLeft:
		self.event = EventLeft
	case rl.KeyRight:
		self.event = EventRight
	}
	return self.event
}

func DrawFood(food Vec2) {
	rl.DrawCircle(int32(food.x*(Factor+LineWidth)+Factor/2),
		int32(food.y*(Factor+LineWidth)+Factor/2), Factor/2, ColorFood)
}

func DrawGrid() {
	for i := 0; i != ColumnCount; i++ {
		rl.DrawRectangle(int32(i*(Factor+LineWidth)+Factor),
			0, LineWidth, GridHeight, ColorLine)
	}
	for i := 0; i != RowCount; i++ {
		rl.DrawRectangle(0, int32(i*(Factor+LineWidth)+Factor),
			GridWidth, LineWidth, ColorLine)
	}
}

func DrawSnake(snake Snake) {
	for i := 1; i != len(snake); i++ {
		rl.DrawRectangle(int32(snake[i].x*(Factor+LineWidth)),
			int32(snake[i].y*(Factor+LineWidth)), Factor, Factor, ColorTail)
	}
	rl.DrawRectangle(int32(snake[0].x*(Factor+LineWidth)),
		int32(snake[0].y*(Factor+LineWidth)), Factor, Factor, ColorHead)
}

func DrawScore(score int) {
	rl.DrawText(fmt.Sprintf("%d", score), 0, GridHeight, FontSize, ColorScore)
}

func DrawWorld(w *World) {
	rl.BeginDrawing()

	rl.ClearBackground(ColorBackground)

	DrawGrid()

	DrawSnake(w.snake)

	DrawFood(w.food)

	DrawScore(w.score)

	rl.EndDrawing()
}

func main() {
	var con Controller
	var ev int
	var lastUpdateTime float64
	var world World

	if len(os.Args) > 1 && os.Args[1] == "-v" {
		fmt.Fprintf(os.Stderr, "ahi %s\n", Version)
		return
	}

	rl.InitWindow(WindowWidth, WindowHeight, WindowTitle)
	defer rl.CloseWindow()

	rl.SetTargetFPS(FPS)

	world.Init()
	con.event = EventNone
	lastUpdateTime = rl.GetTime()

	for !rl.WindowShouldClose() && !world.win {
		DrawWorld(&world)
		ev = con.NextEvent()
		if rl.GetTime()-lastUpdateTime > dt {
			world.Update(ev)
			lastUpdateTime = rl.GetTime()
		}
	}
}
