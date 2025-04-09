package main

import rl "github.com/gen2brain/raylib-go/raylib"
import "os"
import "fmt"

const (
	GridWidth    = ColumnCount*Factor + (ColumnCount-1)*LineWidth
	GridHeight   = RowCount*Factor + (RowCount-1)*LineWidth
	WindowWidth  = GridWidth
	WindowHeight = GridHeight + FontSize
	WindowTitle  = "snake"
	FPS          = 6
)

func main() {
	version := "0.1"

	if len(os.Args) > 1 && os.Args[1] == "-v" {
		fmt.Fprintf(os.Stderr, "ahi %s\n", version)
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
