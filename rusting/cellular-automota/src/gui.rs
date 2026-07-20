use std::ops::AddAssign;
use std::process::Output;

use macroquad::prelude::*;

use num_traits::Num;

use crate::maths::*;
use crate::Renderable;

pub struct Changer<'a, T: Num + ToString + AddAssign> {
    val: &'a T,
    increment: T,
    pos: Point<f32>,
    color: Color,
    text_color: Color,
    up_rect: Rect,
    display_rect: Rect,
    down_rect: Rect
}

impl<'a, T: Num + ToString + AddAssign<>> Changer<'a, T> {
    pub fn new(val: &'a T, increment: T, x: f32, y: f32, width:f32, height:f32, color: Color, text_color:Color) -> Self {
        Changer {
            val: val,
            increment: increment,
            pos: Point::new(x, y),
            color: color,
            text_color: text_color,
            up_rect: Rect { x: x, y: y, w: width, h: height/3. },
            display_rect: Rect { x: x, y: y+(height/3.), w: width, h: height/3. },
            down_rect: Rect { x: x, y: y+(height*2./3.), w: width, h: height/3. }
        }
    }

    pub fn check_click(&self, mpos: (f32, f32)) {
        let pos = Vec2::new(mpos.0, mpos.1);
        if self.up_rect.contains(pos) {
            self.val += self.increment;
        }
    }
}

impl<T: Num + ToString + AddAssign> Renderable for Changer<'_, T> {
    fn render(&self) {
        draw_rectangle(self.up_rect.x, self.up_rect.y, self.up_rect.w, self.up_rect.h, self.color);
        draw_rectangle(self.down_rect.x, self.down_rect.y, self.down_rect.w, self.down_rect.h, self.color);
        draw_rectangle(self.display_rect.x, self.display_rect.y, self.display_rect.w, self.display_rect.h, self.color);
        draw_text(self.val.to_string(), self.pos.x, self.pos.y, self.display_rect.h - 2., self.text_color);
    }
}