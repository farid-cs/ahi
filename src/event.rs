use sdl3::EventPump;
use sdl3::event::Event as SdlEvent;
use sdl3::keyboard::Keycode;

use crate::world::Direction;

pub enum Event {
    Quit,
    World(Direction),
}

pub fn next_event(event_pump: &mut EventPump) -> Option<Event> {
    let mut ev: Option<Event> = None;

    for e in event_pump.poll_iter() {
        match e {
            SdlEvent::Quit { .. } => return Some(Event::Quit),
            SdlEvent::KeyDown {
                keycode: Some(key), ..
            } => match key {
                Keycode::Up => _ = ev.get_or_insert(Event::World(Direction::UP)),
                Keycode::Down => _ = ev.get_or_insert(Event::World(Direction::DOWN)),
                Keycode::Left => _ = ev.get_or_insert(Event::World(Direction::LEFT)),
                Keycode::Right => _ = ev.get_or_insert(Event::World(Direction::RIGHT)),
                _ => {}
            },
            _ => {}
        }
    }

    ev
}
