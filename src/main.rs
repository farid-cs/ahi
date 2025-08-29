use std::env;
use std::process::ExitCode;
use std::time::{Duration, Instant};

mod draw;
mod event;
mod world;
use draw::*;
use event::*;
use world::World;

const WINDOW_TITLE: &str = concat!("ahi ", env!("CARGO_PKG_VERSION"));
const WINDOW_WIDTH: u32 = GRID_WIDTH as u32;
const WINDOW_HEIGHT: u32 = GRID_HEIGHT as u32;
const MIN_STATE_DURATION: Duration = Duration::from_millis(200);

fn main() -> ExitCode {
    let args: Vec<String> = env::args().collect();

    if args.len() > 1 {
        if args[1] != "-v" {
            eprintln!("{} [-v]", args[0]);
            return ExitCode::FAILURE;
        }
        println!("{WINDOW_TITLE}");
        return ExitCode::SUCCESS;
    }

    /* setup */
    let sdl = sdl3::init().unwrap();
    let video = sdl.video().unwrap();
    let window = video
        .window(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)
        .position_centered()
        .build()
        .unwrap();
    let mut pen = Pen::new(window);
    let mut el = EventListener::new(&sdl);
    let mut world = World::new();
    let mut last_update_time = Instant::now();

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
