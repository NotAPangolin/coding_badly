use macroquad::prelude::*;

pub struct Point {
    pos:Vec2,
    r:f32,
    color:Color
}
impl Point {
    pub fn new(x:f32, y:f32, r:f32, color:Color) -> Point {
        Point { pos:Vec2::new(x, y), r:r, color:color }
    }
}

pub struct PointManager {
    pub points: Vec<Point>
}

impl PointManager {
    pub fn new() -> PointManager {
        PointManager {points: vec![]}
    }
    pub fn add_point(&mut self, point:Point) {
        self.points.push( point );
    }
    pub fn render(&self, offset:Vec2) {
        for point in self.points.iter() {
            let draw_pos = point.pos - offset;
            draw_circle(draw_pos.x, draw_pos.y, point.r, point.color);
        }
    }
}