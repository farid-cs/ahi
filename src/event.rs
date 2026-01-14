use sdl3::event::Event as SdlEvent;
use sdl3::keyboard::Keycode;
use sdl3::{EventPump, Sdl};

use crate::world::WorldEvent;

pub enum Event {
    Quit,
    World(WorldEvent),
}

pub struct EventListener {
    event_pump: EventPump,
}

impl EventListener {
    pub fn new(sdl: &Sdl) -> Self {
        Self {
            event_pump: sdl.event_pump().unwrap(),
        }
    }
    pub fn next(&mut self) -> Option<Event> {
        let mut ev: Option<Event> = None;

        while let Some(e) = self.event_pump.poll_event() {
            match e {
                SdlEvent::Quit { .. } => return Some(Event::Quit),
                SdlEvent::KeyDown {
                    keycode: Some(key), ..
                } => match key {
                    Keycode::Up => ev = ev.or(Some(Event::World(WorldEvent::Up))),
                    Keycode::Down => ev = ev.or(Some(Event::World(WorldEvent::Down))),
                    Keycode::Left => ev = ev.or(Some(Event::World(WorldEvent::Left))),
                    Keycode::Right => ev = ev.or(Some(Event::World(WorldEvent::Right))),
                    _ => {}
                },
                _ => {}
            }
        }

        ev
    }
}
