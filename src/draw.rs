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

fn draw_grid(canvas: &mut Canvas<Window>) {
    let mut rect = Rect::new(0, 0, 0, 0);

    canvas.set_draw_color(COLOR_GRID);

    for line in 0..COLUMN_COUNT - 1 {
        rect.set_x(i32::from(line * (CELL_WIDTH + LINE_WIDTH) + CELL_WIDTH));
        rect.set_y(0);
        rect.set_width(LINE_WIDTH.into());
        rect.set_height(GRID_HEIGHT.into());
        canvas.fill_rect(rect).unwrap();
    }

    for line in 0..ROW_COUNT {
        rect.set_x(0);
        rect.set_y(i32::from(line * (CELL_WIDTH + LINE_WIDTH) + CELL_WIDTH));
        rect.set_width(GRID_WIDTH.into());
        rect.set_height(LINE_WIDTH.into());
        canvas.fill_rect(rect).unwrap();
    }
}

fn draw_cell(canvas: &mut Canvas<Window>, pos: Position) {
    let rect = Rect::new(
        i32::try_from(pos.x * (CELL_WIDTH + LINE_WIDTH)).unwrap(),
        i32::try_from(pos.y * (CELL_WIDTH + LINE_WIDTH)).unwrap(),
        CELL_WIDTH.into(),
        CELL_WIDTH.into(),
    );

    canvas.fill_rect(rect).unwrap();
}

fn draw_snake(canvas: &mut Canvas<Window>, snake: &Snake) {
    canvas.set_draw_color(COLOR_HEAD);
    draw_cell(canvas, snake.body[0]);

    canvas.set_draw_color(COLOR_BODY);
    for segment in &snake.body[1..] {
        draw_cell(canvas, *segment);
    }
}

fn draw_food(canvas: &mut Canvas<Window>, food: Position) {
    canvas.set_draw_color(COLOR_FOOD);
    draw_cell(canvas, food);
}

pub fn draw(canvas: &mut Canvas<Window>, w: &World) {
    canvas.set_draw_color(COLOR_BACKGROUND);
    canvas.clear();

    draw_grid(canvas);
    draw_snake(canvas, &w.snake);
    draw_food(canvas, w.food);

    canvas.present();
}
