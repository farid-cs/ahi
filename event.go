package main

import rl "github.com/gen2brain/raylib-go/raylib"

type Controller struct {
	event int
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
