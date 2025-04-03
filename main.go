package main

import rl "github.com/gen2brain/raylib-go/raylib"

const (
	GridWidth    = ColumnCount*Factor + (ColumnCount-1)*LineWidth
	GridHeight   = RowCount*Factor + (RowCount-1)*LineWidth
	WindowWidth  = GridWidth
	WindowHeight = GridHeight + FontSize
	WindowTitle  = "snake"
	FPS          = 6
)

func main() {
	rl.InitWindow(WindowWidth, WindowHeight, WindowTitle)
	defer rl.CloseWindow()

	rl.SetTargetFPS(FPS)

	InitState()

	for !rl.WindowShouldClose() && !win {
		DrawFrame()
		UpdateState()
	}
}
