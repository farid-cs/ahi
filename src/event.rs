use sdl3::event::Event as SdlEvent;
use sdl3::keyboard::Keycode;
use sdl3::EventPump;

use crate::world::WorldEvent;

pub enum Event {
    Quit,
    World(WorldEvent),
}

pub fn next_event(event_pump: &mut EventPump) -> Option<Event> {
    let mut ev: Option<Event> = None;

    for e in event_pump.poll_iter() {
        match e {
            SdlEvent::Quit { .. } => return Some(Event::Quit),
            SdlEvent::KeyDown {
                keycode: Some(key), ..
            } => match key {
                Keycode::Up => _ = ev.get_or_insert(Event::World(WorldEvent::Up)),
                Keycode::Down => _ = ev.get_or_insert(Event::World(WorldEvent::Down)),
                Keycode::Left => _ = ev.get_or_insert(Event::World(WorldEvent::Left)),
                Keycode::Right => _ = ev.get_or_insert(Event::World(WorldEvent::Right)),
                _ => {}
            },
            _ => {}
        }
    }

    ev
}
