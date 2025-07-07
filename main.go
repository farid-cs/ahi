package main

import rl "github.com/gen2brain/raylib-go/raylib"

import "fmt"
import "os"

const (
	Version = "0.2"

	WindowTitle  = "ahi " + Version
	WindowWidth  = GridWidth
	WindowHeight = GridHeight + FontSize

	FPS = 120

	dt = 1.0 / 5.0
)

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
