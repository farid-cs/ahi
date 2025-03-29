package main

import rl "github.com/gen2brain/raylib-go/raylib"

const (
	GRID_WIDTH = COLUMN_COUNT * FACTOR + (COLUMN_COUNT - 1) * LINE_WIDTH
	GRID_HEIGHT = ROW_COUNT * FACTOR + (ROW_COUNT - 1) * LINE_WIDTH
	WINDOW_WIDTH = GRID_WIDTH
	WINDOW_HEIGHT = GRID_HEIGHT + FONT_SIZE
	WINDOW_TITLE = "snake"
	FPS = 6
)

func main() {
	rl.InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE)
	defer rl.CloseWindow()

	rl.SetTargetFPS(FPS)

	init_state()

	for !rl.WindowShouldClose() && !win {
		draw_frame()
		update_state()
	}
}
