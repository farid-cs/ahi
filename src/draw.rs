use sdl3::pixels::Color;
use sdl3::rect::Rect;
use sdl3::render::Canvas;
use sdl3::video::Window;

use crate::world::{COLUMN_COUNT, Position, ROW_COUNT, Snake, World};

const CELL_WIDTH: u16 = 90;
const LINE_WIDTH: u16 = 1;
pub const GRID_WIDTH: u16 = COLUMN_COUNT * CELL_WIDTH + (COLUMN_COUNT - 1) * LINE_WIDTH;
pub const GRID_HEIGHT: u16 = ROW_COUNT * CELL_WIDTH + ROW_COUNT * LINE_WIDTH;

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
            rect.set_x(i32::from(line * (CELL_WIDTH + LINE_WIDTH) + CELL_WIDTH));
            rect.set_y(0);
            rect.set_width(LINE_WIDTH.into());
            rect.set_height(GRID_HEIGHT.into());
            self.canvas.fill_rect(rect).unwrap();
        }

        for line in 0..ROW_COUNT {
            rect.set_x(0);
            rect.set_y(i32::from(line * (CELL_WIDTH + LINE_WIDTH) + CELL_WIDTH));
            rect.set_width(GRID_WIDTH.into());
            rect.set_height(LINE_WIDTH.into());
            self.canvas.fill_rect(rect).unwrap();
        }
    }
    fn draw_cell(&mut self, pos: Position) {
        let rect = Rect::new(
            i32::try_from(pos.x * (CELL_WIDTH + LINE_WIDTH)).unwrap(),
            i32::try_from(pos.y * (CELL_WIDTH + LINE_WIDTH)).unwrap(),
            CELL_WIDTH.into(),
            CELL_WIDTH.into(),
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
