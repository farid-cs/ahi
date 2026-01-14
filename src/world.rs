use std::cmp;

pub const COLUMN_COUNT: u32 = 16;
pub const ROW_COUNT: u32 = 10;
const INITIAL_POSITION: Position = Position {
    x: COLUMN_COUNT / 2,
    y: ROW_COUNT / 2,
};

#[derive(Copy, Clone, PartialEq, Debug)]
pub struct Position {
    pub x: u32,
    pub y: u32,
}

#[derive(Copy, Clone, PartialEq, Debug)]
pub struct Direction {
    pub x: i8,
    pub y: i8,
}

pub enum WorldEvent {
    Up,
    Right,
    Down,
    Left,
}

pub struct Snake {
    pub body: Vec<Position>,
}

pub struct World {
    pub snake: Snake,
    pub food: Position,
    pub direction: Direction,
    pub score: u64,
    pub win: bool,
}

impl Direction {
    const UP: Self = Self { x: 0, y: -1 };
    const RIGHT: Self = Self { x: 1, y: 0 };
    const DOWN: Self = Self { x: 0, y: 1 };
    const LEFT: Self = Self { x: -1, y: 0 };
}

fn spawn_food(snake: &Snake) -> Position {
    for x in 0..COLUMN_COUNT {
        for y in 0..ROW_COUNT {
            let pos = Position { x, y };

            if !snake.body.contains(&pos) {
                return pos;
            }
        }
    }
    unreachable!();
}

impl Snake {
    fn new() -> Self {
        let mut body = Vec::with_capacity(usize::try_from(COLUMN_COUNT * ROW_COUNT).unwrap());

        body.push(INITIAL_POSITION);

        Self { body }
    }
    fn step(&mut self, direction: Direction) -> bool {
        let range = 0..self.body.len() - 1;
        self.body.copy_within(range, 1);
        let mut head = self.body[0];

        if direction.x < 0 {
            head.x = head.x.wrapping_sub(1);
            head.x = cmp::min(head.x, COLUMN_COUNT - 1);
        } else {
            head.x += direction.x as u32;
            head.x %= COLUMN_COUNT;
        }
        if direction.y < 0 {
            head.y = head.y.wrapping_sub(1);
            head.y = cmp::min(head.y, ROW_COUNT - 1);
        } else {
            head.y += direction.y as u32;
            head.y %= ROW_COUNT;
        }
        self.body[0] = head;

        if self.body[1..].contains(&head) {
            return false;
        }

        true
    }
}

impl World {
    pub fn new() -> Self {
        let snake = Snake::new();
        let food = spawn_food(&snake);

        World {
            snake,
            food,
            direction: Direction::RIGHT,
            score: 0,
            win: false,
        }
    }
    pub fn handle(&mut self, ev: &WorldEvent) {
        let direction = match ev {
            WorldEvent::Up => Direction::UP,
            WorldEvent::Down => Direction::DOWN,
            WorldEvent::Left => Direction::LEFT,
            WorldEvent::Right => Direction::RIGHT,
        };

        if direction.x * self.direction.x + direction.y * self.direction.y == 0 {
            self.direction = direction;
        }
    }
    pub fn update(&mut self) {
        let last_segment = self.snake.body[self.snake.body.len() - 1];

        if !self.snake.step(self.direction) {
            *self = World::new();
            return;
        }

        if self.snake.body[0] == self.food {
            self.snake.body.push(last_segment);
            if self.snake.body.len() == (COLUMN_COUNT * ROW_COUNT) as usize {
                self.win = true;
                return;
            }
            self.score += 1;
            self.food = spawn_food(&self.snake);
        }
    }
}
