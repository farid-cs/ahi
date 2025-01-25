package main

import rl "github.com/gen2brain/raylib-go/raylib"

const (
	EVENT_NONE = iota
	EVENT_LEFT
	EVENT_RIGHT
	EVENT_UP
	EVENT_DOWN
	EVENT_CLOSE
)

func next_event() int {
	switch rl.GetKeyPressed() {
	case rl.KeyUp:
		return EVENT_UP
	case rl.KeyDown:
		return EVENT_DOWN
	case rl.KeyLeft:
		return EVENT_LEFT
	case rl.KeyRight:
		return EVENT_RIGHT
	}
	return EVENT_NONE
}
