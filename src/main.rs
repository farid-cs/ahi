use std::env;
use std::process::ExitCode;
use std::time::{Duration, Instant};

use draw::{GRID_HEIGHT, GRID_WIDTH, draw_scene};
use event::{Event, next_event};
use world::{Direction, World};

mod draw;
mod event;
mod world;

const WINDOW_TITLE: &str = concat!("ahi ", env!("CARGO_PKG_VERSION"));
const WINDOW_WIDTH: u16 = GRID_WIDTH;
const WINDOW_HEIGHT: u16 = GRID_HEIGHT;
const MIN_STATE_DURATION: Duration = Duration::from_millis(200);

fn main() -> ExitCode {
    let args: Vec<_> = env::args().collect();

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
    let mut canvas = video
        .window(WINDOW_TITLE, WINDOW_WIDTH.into(), WINDOW_HEIGHT.into())
        .position_centered()
        .build()
        .unwrap()
        .into_canvas();
    let mut event_pump = sdl.event_pump().unwrap();
    let mut world = World::new();
    let mut last_redraw_time;
    let mut dir: Option<Direction> = None;

    /* run */
    draw_scene(&mut canvas, &world);
    last_redraw_time = Instant::now();
    while !world.win {
        if let Some(ev) = next_event(&mut event_pump) {
            match ev {
                Event::Quit => break,
                Event::World(w) => dir = dir.or(Some(w)),
            }
        }
        if last_redraw_time.elapsed() > MIN_STATE_DURATION {
            world.update(dir);
            dir = None;
            draw_scene(&mut canvas, &world);
            last_redraw_time = Instant::now();
        }
    }

    ExitCode::SUCCESS
}
