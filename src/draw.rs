use sdl3::pixels::Color;
use sdl3::rect::Rect;
use sdl3::render::Canvas;
use sdl3::video::Window;

use crate::world::{COLUMN_COUNT, Position, ROW_COUNT, Snake, World};

const FACTOR: u64 = 90;

const LINE_WIDTH: u64 = 1;
pub const GRID_WIDTH: u64 = COLUMN_COUNT * FACTOR + (COLUMN_COUNT - 1) * LINE_WIDTH;
pub const GRID_HEIGHT: u64 = ROW_COUNT * FACTOR + ROW_COUNT * LINE_WIDTH;

const COLOR_BACKGROUND: Color = Color::RGBA(0xBE, 0xBE, 0xBE, 0xFF);
const COLOR_GRID: Color = Color::RGBA(0x00, 0x00, 0x00, 0xFF);
const COLOR_HEAD: Color = Color::RGBA(0x00, 0xFF, 0x00, 0xFF);
const COLOR_BODY: Color = Color::RGBA(0xFF, 0xFF, 0x00, 0xFF);
const COLOR_FOOD: Color = Color::RGBA(0x00, 0x00, 0xFF, 0xFF);

pub struct Pen {
    canvas: Canvas<Window>,
}

impl Pen {
    pub fn new(window: Window) -> Self {
        Self {
            canvas: window.into_canvas(),
        }
    }
    fn draw_grid(&mut self) {
        let mut rect = Rect::new(0, 0, 0, 0);

        self.canvas.set_draw_color(COLOR_GRID);

        for line in 0..COLUMN_COUNT - 1 {
            rect.set_x((line * (FACTOR + LINE_WIDTH) + (FACTOR)) as i32);
            rect.set_y(0);
            rect.set_width(LINE_WIDTH as u32);
            rect.set_height(GRID_HEIGHT as u32);
            self.canvas.fill_rect(rect).unwrap();
        }

        for line in 0..ROW_COUNT {
            rect.set_x(0);
            rect.set_y((line * (FACTOR + LINE_WIDTH) + FACTOR) as i32);
            rect.set_width(GRID_WIDTH as u32);
            rect.set_height(LINE_WIDTH as u32);
            self.canvas.fill_rect(rect).unwrap();
        }
    }
    fn draw_cell(&mut self, pos: Position) {
        let rect = Rect::new(
            (pos.x * (FACTOR + LINE_WIDTH)) as i32,
            (pos.y * (FACTOR + LINE_WIDTH)) as i32,
            FACTOR as u32,
            FACTOR as u32,
        );

        self.canvas.fill_rect(rect).unwrap();
    }
    fn draw_snake(&mut self, snake: &Snake) {
        let head = snake.body[0];

        self.canvas.set_draw_color(COLOR_BODY);
        for segment in &snake.body[1..] {
            self.draw_cell(*segment);
        }

        self.canvas.set_draw_color(COLOR_HEAD);
        self.draw_cell(head);
    }
    fn draw_food(&mut self, food: Position) {
        self.canvas.set_draw_color(COLOR_FOOD);
        self.draw_cell(food);
    }
    pub fn draw(&mut self, w: &World) {
        self.canvas.set_draw_color(COLOR_BACKGROUND);
        self.canvas.clear();

        self.draw_grid();
        self.draw_snake(&w.snake);
        self.draw_food(w.food);

        self.canvas.present();
    }
}
