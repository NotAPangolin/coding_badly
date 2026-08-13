use std::{ops::{Add, AddAssign, Sub, SubAssign}, process::Output};

use num_traits::Num;

use macroquad::prelude::*;

#[derive(PartialEq, Eq, Hash, Clone, Copy)]
pub struct Point<T: Num + Sized> {
    pub x: T,
    pub y: T
}
impl<T: Num> Point<T> {
    pub fn new(x: T, y: T) -> Self {
        Point {
            x: x,
            y: y
        }
    }
}
impl<T: Num> Add for Point<T> {
    type Output = Self;

    fn add(self, rhs: Self) -> Self::Output {
        Point {
            x: self.x + rhs.x,
            y: self.y + rhs.y
        }
    }
}
impl<T: UsableNumber> AddAssign for Point<T> {
    fn add_assign(&mut self, rhs: Self) {
        self.x += rhs.x;
        self.y += rhs.y;
    }
}

// Usable Number trait def

pub trait UsableNumber: Num + ToString + Add<Output = Self> + AddAssign + Sub<Output = Self> + SubAssign + Copy {}

impl UsableNumber for f32 {}


// dumbass helper thingy

pub fn xy_to_screen(x:f32, y:f32) -> Point<f32> {
    let screen_x =  if x < 0. {screen_width() + x} else {x};
    let screen_y =  if y < 0. {screen_height() + y} else {y};
    Point { x: screen_x, y: screen_y }
}

