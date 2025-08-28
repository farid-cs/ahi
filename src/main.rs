use std::env;
use std::process::ExitCode;
use std::time::{Duration, Instant};

mod draw;
mod event;
mod world;
use draw::*;
use event::*;
use world::World;

const VERSION: &str = env!("CARGO_PKG_VERSION");
const WINDOW_WIDTH: u64 = GRID_WIDTH;
const WINDOW_HEIGHT: u64 = GRID_HEIGHT;
const MIN_STATE_DURATION: Duration = Duration::from_millis(200);

fn main() -> ExitCode {
    let args: Vec<String> = env::args().collect();
    let mut world = World::new();
    let mut last_update_time: Instant;

    if args.len() > 1 {
        if args[1] != "-v" {
            eprintln!("{} [-v]", args[0]);
            return ExitCode::FAILURE;
        }
        println!("ahi {}", VERSION);
        return ExitCode::SUCCESS;
    }

    /* setup */
    let sdl = sdl3::init().unwrap();
    let video = sdl.video().unwrap();
    let window = video
        .window(format!("ahi {}", VERSION).as_str(), WINDOW_WIDTH as u32, WINDOW_HEIGHT as u32)
        .position_centered()
        .build()
        .unwrap();
    let mut pen = Pen::new(window);
    let event_pump = sdl.event_pump().unwrap();
    let mut el = EventListener::new(event_pump);
    last_update_time = Instant::now();

    /* run */
    while el.listen() && !world.win {
        pen.draw(&world);
        if last_update_time.elapsed() > MIN_STATE_DURATION {
            el.handle(&mut world);
            world.update();
            last_update_time = Instant::now();
        }
    }

    ExitCode::SUCCESS
}
