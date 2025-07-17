#include "raylib.h"

#include "event.h"

Event Controller::NextEvent(this Controller &self) {
	switch (GetKeyPressed()) {
	case KEY_UP:
		self.event = Event::Up;
		break;
	case KEY_DOWN:
		self.event = Event::Down;
		break;
	case KEY_LEFT:
		self.event = Event::Left;
		break;
	case KEY_RIGHT:
		self.event = Event::Right;
		break;
	}
	return self.event;
}
