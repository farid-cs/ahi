use std::cmp;

pub const COLUMN_COUNT: u16 = 16;
pub const ROW_COUNT: u16 = 10;
const INITIAL_POSITION: Position = Position {
    x: COLUMN_COUNT / 2,
    y: ROW_COUNT / 2,
};

#[derive(Copy, Clone, PartialEq, Debug)]
pub struct Position {
    pub x: u16,
    pub y: u16,
}

#[derive(Clone, Copy, PartialEq, Debug)]
pub struct Direction {
    pub x: i8,
    pub y: i8,
}

enum Block {
    Empty,
    Snake,
    Food,
}

pub struct Snake {
    pub body: Vec<Position>,
    pub dir: Direction,
}

pub struct World {
    pub snake: Snake,
    pub food: Position,
    pub score: u64,
    pub win: bool,
}

impl Direction {
    pub const UP: Self = Self { x: 0, y: -1 };
    pub const RIGHT: Self = Self { x: 1, y: 0 };
    pub const DOWN: Self = Self { x: 0, y: 1 };
    pub const LEFT: Self = Self { x: -1, y: 0 };
}

fn spawn_food(body: &[Position]) -> Position {
    for x in 0..COLUMN_COUNT {
        for y in 0..ROW_COUNT {
            let pos = Position { x, y };

            if !body.contains(&pos) {
                return pos;
            }
        }
    }

    unreachable!();
}

impl Snake {
    fn new() -> Self {
        let mut body = Vec::with_capacity(usize::from(COLUMN_COUNT * ROW_COUNT));

        body.push(INITIAL_POSITION);

        Self {
            body,
            dir: Direction::RIGHT,
        }
    }
    fn turn(&mut self, direction: Direction) {
        if direction.x * self.dir.x + direction.y * self.dir.y == 0 {
            self.dir = direction;
        }
    }
    fn step(&mut self, food: Position) -> Block {
        let last_segment = *self.body.last().unwrap();
        let range = 0..self.body.len() - 1;
        self.body.copy_within(range, 1);
        let mut head = self.body[0];

        if self.dir.x < 0 {
            head.x = head.x.wrapping_sub(1);
            head.x = cmp::min(head.x, COLUMN_COUNT - 1);
        } else {
            head.x += u16::try_from(self.dir.x).unwrap();
            head.x %= COLUMN_COUNT;
        }
        if self.dir.y < 0 {
            head.y = head.y.wrapping_sub(1);
            head.y = cmp::min(head.y, ROW_COUNT - 1);
        } else {
            head.y += u16::try_from(self.dir.y).unwrap();
            head.y %= ROW_COUNT;
        }
        self.body[0] = head;

        if self.body[1..].contains(&head) {
            return Block::Snake;
        }

        if head == food {
            self.body.push(last_segment);
            return Block::Food;
        }

        Block::Empty
    }
}

impl World {
    pub fn new() -> Self {
        let snake = Snake::new();
        let food = spawn_food(&snake.body);

        World {
            snake,
            food,
            score: 0,
            win: false,
        }
    }
    pub fn update(&mut self, dir: Option<Direction>) {
        if let Some(dir) = dir {
            self.snake.turn(dir);
        }

        match self.snake.step(self.food) {
            Block::Empty => (),
            Block::Snake => *self = World::new(),
            Block::Food => {
                if self.snake.body.len() == usize::from(COLUMN_COUNT * ROW_COUNT) {
                    self.win = true;
                    return;
                }
                self.score += 1;
                self.food = spawn_food(&self.snake.body);
            }
        }
    }
}
