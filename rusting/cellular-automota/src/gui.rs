use macroquad::prelude::*;

use crate::maths::*;
use crate::ScreenRenderable;

/*--------------------GUI Container Obj--------------------*/
pub struct GUI<> {
    text_items: Vec<TextItem>,
    incs: Vec<Incrementable<f32>>
}
impl GUI {
    pub fn new() -> Self {
        GUI { text_items: vec![], incs: vec![] }
    }

    pub fn new_text_item(&mut self, text: String, x: f32, y: f32, font_size: f32, color: Color) -> &TextItem {
        self.text_items.push(TextItem::new(text, x, y, font_size, color));

        self.text_items.get(self.text_items.len()-1).unwrap()
    }
    pub fn new_incrementable(&mut self, prefix: &'static str, suffix: &'static str, initial_val: f32, increment: f32, x: f32, y: f32, width: f32, height: f32, color: Color, text_color: Color) -> &Incrementable<f32> {
        let Point {x: screen_x, y: screen_y} = xy_to_screen(x, y);
        
        self.incs.push(Incrementable::new(prefix, suffix, initial_val, increment, screen_x, screen_y, width, height, color, text_color));
        self.incs.get(self.incs.len()-1).unwrap()
    }

    pub fn check_click(&mut self, mpos: (f32, f32)) {
        for inc in self.incs.as_mut_slice() {
            inc.check_click(mpos);
        }
    }
}
impl ScreenRenderable for GUI {
    fn render(&self) {
        for item in self.text_items.as_slice() {
            item.render();
        }
        for inc in self.incs.as_slice() {
            inc.render();
        }
    }
}

/*--------------------Text Item--------------------*/
pub struct TextItem {
    text:       String,
    pos:        Point<f32>,
    font_size:  f32,
    color:      Color
}
impl ScreenRenderable for TextItem {
    fn render(&self) {
        draw_text(&self.text, self.pos.x, self.pos.y, self.font_size, self.color);
    }
}
impl TextItem {
    pub fn new(text: String, x: f32, y: f32, font_size: f32, color: Color) -> Self {
        TextItem { text, pos: xy_to_screen(x, y), font_size, color }
    }
    
    pub fn set_text(&mut self, new_val: String) {
        self.text = new_val;
    }
}

/*--------------------Incrementable--------------------*/
pub struct Incrementable<T: UsableNumber> {
    val:            T,
    increment:      T,
    
    prefix:         &'static str,
    suffix:         &'static str,

    pos:            Point<f32>,
    color:          Color,
    up_rect:        Rect,
    display_rect:   Rect,
    down_rect:      Rect,
    label:          TextItem,
}

impl<T: UsableNumber> Incrementable<T> {
    pub fn new(prefix: &'static str, suffix: &'static str, initial_val: T, increment: T, x: f32, y: f32, width:f32, height:f32, color: Color, text_color:Color) -> Self {
        Incrementable {
            val: initial_val,
            increment: increment,

            prefix,
            suffix,

            pos: Point::new(x, y),
            color: color,
            up_rect: Rect { x: x, y: y, w: width, h: height/3. },
            display_rect: Rect { x: x, y: y+(height/3.), w: width, h: height/3. },
            down_rect: Rect { x: x, y: y+(height*2./3.), w: width, h: height/3. },
            label: TextItem { text: prefix.to_owned() + &initial_val.to_string() + suffix, pos: Point::new(x, y+(height*2./3.)), font_size: height/3., color: text_color }
        }
    }

    pub fn check_click(&mut self, mpos: (f32, f32)) {
        let pos = Vec2::new(mpos.0, mpos.1);
        if self.up_rect.contains(pos) {
            self.val += self.increment;
            self.label.set_text(self.prefix.to_owned() + &self.val.to_string() + self.suffix);
        } if self.down_rect.contains(pos) {
            self.val -= self.increment;
            self.label.set_text(self.prefix.to_owned() + &self.val.to_string() + self.suffix);
        }
    }
}

impl<T: UsableNumber> ScreenRenderable for Incrementable<T> {
    fn render(&self) {
        draw_rectangle(self.up_rect.x, self.up_rect.y, self.up_rect.w, self.up_rect.h, self.color);
        draw_rectangle_lines(self.up_rect.x, self.up_rect.y, self.up_rect.w, self.up_rect.h, self.up_rect.h * 0.1, BLACK);

        draw_rectangle(self.down_rect.x, self.down_rect.y, self.down_rect.w, self.down_rect.h, self.color);
        draw_rectangle_lines(self.down_rect.x, self.down_rect.y, self.down_rect.w, self.down_rect.h, self.down_rect.h * 0.1, BLACK);

        draw_rectangle(self.display_rect.x, self.display_rect.y, self.display_rect.w, self.display_rect.h, self.color);
        self.label.render();
    }
}