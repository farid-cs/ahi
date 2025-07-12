#ifndef AHI_EVENT_H
#define AHI_EVENT_H

#include "world.h"

struct Controller {
	Event event;
	constexpr Controller() : event{Event::None} {}
	Event NextEvent();
};

#endif
