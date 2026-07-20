use std::collections::HashMap;

use ::rand::{prelude::*, random};
use macroquad::prelude::*;

use crate::maths::Point;

pub struct Board {
    data: HashMap<Point<i32>, bool>,

    tile_size: f32
}

impl Board {
    pub fn new() -> Self {
        Board {
            data: HashMap::new(),
            tile_size: 16f32
        }
    }

    // pub fn get(self, coord: &Point<T>) -> bool {
    //     if self.data.contains_key(coord) { 
    //         self.data[coord]
    //     } else {
    //         false
    //     }
    // }
    pub fn get(&self, x: i32, y: i32) -> bool {
        let coord: &Point<i32> = &Point::new(x, y);
        if self.data.contains_key(coord) { 
            self.data[coord]
        } else {
            false
        }
    }

    pub fn set(&mut self, coord: Point<i32>, val: bool) {
        self.data.insert(coord, val);
    }  

    pub fn rand_fill(&mut self) {
        for x in 0..20 {
            for y in 0..20 {
                self.set(Point::new(x,y), random::<bool>());
            }
        }
    }

    pub fn render(&self, render_offset: &Vec2) {
        let height_in_tiles: f32 = screen_height() / (self.tile_size + 1.);
        let width_in_tiles: f32 = screen_width() / (self.tile_size + 1.);
        for x in -2..(width_in_tiles) as i32 {
            for y in -2..(height_in_tiles) as i32 {
                if self.get(x - (render_offset.x / self.tile_size) as i32, y - (render_offset.y / self.tile_size) as i32) {
                    draw_rectangle(
                        x as f32 * self.tile_size + render_offset.x % self.tile_size,
                        y as f32 * self.tile_size + render_offset.y % self.tile_size,
                        self.tile_size,
                        self.tile_size,
                        BLACK
                    );
                }
            }
        }
        // for x in 0..20 {
        //     for y in 0..20 {
        //         draw_rectangle(
        //             x as f32 * (self.tile_size+1.) + render_offset.x,
        //             y as f32 * (self.tile_size+1.) + render_offset.y,
        //             self.tile_size,
        //             self.tile_size,
        //             if self.get(&Point::new(x,y)) {WHITE} else {BLACK}
        //         );
        //     }
        // }
        // for x in -2..(screen_width() / (self.tile_size+1f32)).round() as i32 + 2 {
        //     for y in -2..(screen_height() / (self.tile_size+1f32)).round() as i32 + 2 {
        //         // let crnt_scrn_point = Vec2::new(
        //         //     x as f32 * self.tile_size + render_offset.x,
        //         //     y as f32 * self.tile_size + render_offset.y
        //         // );

        //         draw_rectangle(
        //             x as f32 * self.tile_size + render_offset.x,
        //             y as f32 * self.tile_size + render_offset.y,
        //             self.tile_size,
        //             self.tile_size,
        //             if self.get(&Point::new(x,y)) {WHITE} else {BLACK}
        //         );
        //     }
        // }
        // for x in -2..(screen_width() / (self.tile_size + 1.)) as i32 + 2 {
        //     for y in -2..(screen_height() / (self.tile_size + 1.)) as i32 + 2 {
        //         // if self.get(&Point::new(x, y)) {
        //         //     draw_rectangle(
        //         //         x as f32 * self.tile_size + render_offset.x % self.tile_size,
        //         //         y as f32 * self.tile_size + render_offset.y % self.tile_size,
        //         //         self.tile_size,
        //         //         self.tile_size,
        //         //         if self.get(&Point::new(
        //         //             x - (render_offset.x / (self.tile_size + 1.)).round() as i32,
        //         //             y - (render_offset.y / (self.tile_size + 1.)).round() as i32
        //         //         )) {WHITE} else {BLACK}
        //         //     );
        //         // }
        //         // for x in range(cam_offset[0] // self.tile_size, (cam_offset[0] + surf.get_width()) // self.tile_size + 1):
        //         //     for y in range(cam_offset[1] // self.tile_size, (cam_offset[1] + surf.get_height()) // self.tile_size + 1):
        //         //         loc = str(x) + ';' + str(y)
        //         //         if loc in self.tilemap:
        //         //             tile = self.tilemap[loc]
        //         //             surf.blit(self.game.assets[tile['id']][tile['variant']],
        //         // (tile['pos'][0] * self.tile_size - cam_offset[0],
        //         // tile['pos'][1] * self.tile_size - cam_offset[1]))

        //         for x in ((render_offset.x / self.tile_size) as i32 .. ((render_offset.x + screen_width()) / (self.tile_size + 1.)) as i32) {
        //             for y in ((render_offset.y / self.tile_size) as i32 .. ((render_offset.y + screen_height()) / (self.tile_size + 1.)) as i32) {
        //                 if self.get(&Point::new(x,y)) {
        //                     draw_rectangle(
        //                         x as f32 * self.tile_size + render_offset.x % self.tile_size,
        //                         y as f32 * self.tile_size + render_offset.y % self.tile_size,
        //                         self.tile_size,
        //                         self.tile_size,
        //                         BLACK
        //                     );
        //                 }
        //             }
        //         }
        //     }
        
    }
    // pub fn debug_render(&self, render_offset: &Vec2) {
    //     draw_text("test", 0., 0., 16., BLUE);
    // }
}