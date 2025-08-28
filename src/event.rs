use sdl3::EventPump;
use sdl3::event::Event;
use sdl3::keyboard::Keycode;
use std::collections::VecDeque;

use crate::world::{World, WorldEvent};

pub struct EventListener {
    events: VecDeque<WorldEvent>,
    event_pump: EventPump,
}

impl EventListener {
    pub fn new(event_pump: EventPump) -> Self {
        Self {
            event_pump,
            events: VecDeque::new(),
        }
    }
    pub fn listen(&mut self) -> bool {
        while let Some(e) = self.event_pump.poll_event() {
            match e {
                Event::Quit { .. } => return false,
                Event::KeyDown {
                    keycode: Some(key), ..
                } => match key {
                    Keycode::Up => self.events.push_front(WorldEvent::Up),
                    Keycode::Down => self.events.push_front(WorldEvent::Down),
                    Keycode::Left => self.events.push_front(WorldEvent::Left),
                    Keycode::Right => self.events.push_front(WorldEvent::Right),
                    _ => {}
                },
                _ => {}
            }

            if self.events.len() > 100 {
                self.events.pop_back();
            }
        }

        true
    }
    pub fn handle(&mut self, w: &mut World) {
        if let Some(event) = self.events.front() {
            w.handle(event);
        } else {
            return;
        }
        self.events.pop_front();
    }
}
