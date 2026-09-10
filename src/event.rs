use std::time::{Duration, Instant};

use sdl3::EventPump;
use sdl3::event::Event as SdlEvent;
use sdl3::keyboard::Keycode;

use crate::world::Direction;

pub const MIN_STEP_DURATION: Duration = Duration::from_millis(200);

pub enum Event {
    Quit,
    World(Direction),
}

pub fn next_event(event_pump: &mut EventPump) -> Option<Event> {
    let last_step = Instant::now();
    let mut ev: Option<Event> = None;

    while last_step.elapsed() <= MIN_STEP_DURATION {
        for e in event_pump.poll_iter() {
            match e {
                SdlEvent::Quit { .. } => return Some(Event::Quit),
                SdlEvent::KeyDown {
                    keycode: Some(key), ..
                } => match key {
                    Keycode::Up => ev = Some(Event::World(Direction::UP)),
                    Keycode::Down => ev = Some(Event::World(Direction::DOWN)),
                    Keycode::Left => ev = Some(Event::World(Direction::LEFT)),
                    Keycode::Right => ev = Some(Event::World(Direction::RIGHT)),
                    _ => {}
                },
                _ => {}
            }
        }
    }

    ev
}
