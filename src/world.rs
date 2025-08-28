pub const COLUMN_COUNT: u64 = 16;
pub const ROW_COUNT: u64 = 10;

#[derive(Copy, Clone, PartialEq, Debug)]
pub struct Vec2<T> {
    pub x: T,
    pub y: T,
}
pub type Position = Vec2<u64>;
pub type Direction = Vec2<i64>;

pub enum WorldEvent {
    Up,
    Right,
    Down,
    Left,
}

pub struct Snake {
    pub body: Vec<Position>
}

pub struct World {
    pub snake: Snake,
    pub food: Position,
    pub direction: Direction,
    pub score: u64,
    pub win: bool,
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
        Self { body: vec![Position{ x: COLUMN_COUNT/2, y: ROW_COUNT/2 }] }
    }
    fn step(&mut self, direction: Direction) -> bool {
        let range = 0..self.body.len()-1;
        self.body.copy_within(range, 1);

        if direction.x < 0 {
            if self.body[0].x == 0 {
                self.body[0].x = COLUMN_COUNT;
            }
            self.body[0].x -= -direction.x as u64;
        } else {
            self.body[0].x += direction.x as u64;
        }
        self.body[0].x += COLUMN_COUNT;
        self.body[0].x %= COLUMN_COUNT;

        if direction.y < 0 {
            if self.body[0].y == 0 {
                self.body[0].y = ROW_COUNT;
            }
            self.body[0].y -= -direction.y as u64;
        } else {
            self.body[0].y += direction.y as u64;
        }
        self.body[0].y += ROW_COUNT;
        self.body[0].y %= ROW_COUNT;

        if (&self.body[1..]).contains(&self.body[0]) {
            return false;
        }

        return true;
    }
}

impl World {
    pub fn new() -> Self {
        let snake = Snake::new();
        let food = spawn_food(&snake);

        World {
            snake,
            food,
            direction: Direction { x: 1, y: 0 },
            score: 0,
            win: false,
        }
    }
    pub fn handle(&mut self, ev: &WorldEvent) {
        let direction = match ev {
            WorldEvent::Up => Direction { x: 0, y: -1 },
            WorldEvent::Down => Direction { x: 0, y: 1 },
            WorldEvent::Left => Direction { x: -1, y: 0 },
            WorldEvent::Right => Direction { x: 1, y: 0 },
        };

        if direction.x * self.direction.x + direction.y * self.direction.y == 0 {
            self.direction = direction;
        }
    }
    pub fn update(&mut self) {
        let last_segment = self.snake.body[self.snake.body.len()-1];

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
