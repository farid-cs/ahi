package main

import rl "github.com/gen2brain/raylib-go/raylib"

var grid [10][16]int

const WINDOW_WIDTH = int32(100 * len(grid[0]))
const WINDOW_HEIGHT = int32(100 * len(grid))

func main() {
	rl.InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "snake")
	defer rl.CloseWindow()

	for !rl.WindowShouldClose() {
		rl.BeginDrawing()

		rl.ClearBackground(rl.Red)

		for i := range grid {
			for j := range grid[0] {
				rl.DrawRectangle(
					int32(j * 100 + 2),
					int32(i * 100 + 2),
					96,
					96,
					rl.Green,
				)
			}
		}

		rl.EndDrawing()
	}
}
