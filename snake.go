package main

import rl "github.com/gen2brain/raylib-go/raylib"

const WINDOW_WIDTH = 1600
const WINDOW_HEIGHT = 900

func main() {
	rl.InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "snake")
	defer rl.CloseWindow()

	for !rl.WindowShouldClose() {
		rl.BeginDrawing()
		rl.EndDrawing()
	}
}
