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

var (
	ColorBackground = rl.Gray
	ColorHead       = rl.Green
	ColorTail       = rl.Yellow
	ColorFood       = rl.Blue
	ColorLine       = rl.Black
	ColorScore      = rl.Black

	snake          []Vec2
	food           Vec2
	velocity       Vec2
	newVelocity    Vec2
	win            bool
	score          int
	lastUpdateTime float64
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
	velocity = Vec2{+1, 0}
	newVelocity = velocity
	food = spawnFood()
	score = 0
	lastUpdateTime = rl.GetTime()
}

func UpdateState() {
	lastSegment := snake[len(snake)-1]

	switch rl.GetKeyPressed() {
	case rl.KeyUp:
		newVelocity = Vec2{0, -1}
	case rl.KeyDown:
		newVelocity = Vec2{0, +1}
	case rl.KeyLeft:
		newVelocity = Vec2{-1, 0}
	case rl.KeyRight:
		newVelocity = Vec2{+1, 0}
	}

	if rl.GetTime()-lastUpdateTime <= dt {
		return
	}

	if newVelocity.x*velocity.x+newVelocity.y*velocity.y == 0 {
		velocity = newVelocity
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

	lastUpdateTime = rl.GetTime()
}

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

func main() {
	if len(os.Args) > 1 && os.Args[1] == "-v" {
		fmt.Fprintf(os.Stderr, "ahi %s\n", Version)
		return
	}

	rl.InitWindow(WindowWidth, WindowHeight, WindowTitle)
	defer rl.CloseWindow()

	rl.SetTargetFPS(FPS)

	InitState()

	for !rl.WindowShouldClose() && !win {
		DrawFrame()
		UpdateState()
	}
}
