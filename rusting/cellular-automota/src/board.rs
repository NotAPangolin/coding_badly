use std::collections::{HashMap, HashSet};

use ::rand::{random};
use macroquad::prelude::*;

use crate::maths::Point;
use crate::{CameraRenderable, ScreenRenderable};

#[derive(Hash, Eq, PartialEq)]
pub struct Tile {
    data: i32
}

pub struct Board {
    data: HashMap<Point<i32>, bool>,

    tile_size: f32,
    border_size: f32,

    neighborhood: [Point<i32>; 9] // todo, make flexible and allow for procedural generation of moore-like and other types
}

impl Board {
    pub fn new() -> Self {
        Board {
            data: HashMap::new(),
            tile_size: 16.,
            border_size: 1.,
            neighborhood: [Point::new(-1, -1), Point::new(0, -1), Point::new(1, -1),
                           Point::new(-1,  0), Point::new(0,  0), Point::new(1,  0),
                           Point::new(-1,  1), Point::new(0, -1), Point::new(1,  1)]
        }
    }

    pub fn screen_to_tile(&self, screen_coord: (f32, f32)) -> Point<i32> {
        Point { x: (screen_coord.0 / (self.tile_size + self.border_size)) as i32, y: (screen_coord.1 / (self.tile_size + self.border_size)) as i32 }
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

    pub fn clear(&mut self) {
        self.data.clear();
    }

    pub fn rand_fill(&mut self, size:i32) {
        for x in 0..size {
            for y in 0..size {
                self.set(Point::new(x,y), random::<bool>());
            }
        }
    }

    pub fn get_population(&self) -> i32 {
        self.data.len() as i32
    }
}
impl CameraRenderable for Board {
    fn render(&self, render_offset: &Vec2) {
        let t_b_size = self.tile_size + self.border_size;
        let s_height_in_tiles: f32 = screen_height() / (t_b_size);
        let s_width_in_tiles: f32 = screen_width() / (t_b_size);

        for x in -2..(s_width_in_tiles+2.) as i32 {
            for y in -2..(s_height_in_tiles+2.) as i32 {
                if self.get(x - (render_offset.x / t_b_size) as i32, y - (render_offset.y / t_b_size) as i32) {
                    draw_rectangle(
                        x as f32 * t_b_size + (render_offset.x % t_b_size),
                        y as f32 * t_b_size + (render_offset.y % t_b_size),
                        self.tile_size,
                        self.tile_size,
                        BLACK
                    );
                }
            }
        }        
    }
    fn debug_render(&self, render_offset: &Vec2) {
        let t_b_size = self.tile_size + self.border_size;
        let s_height_in_tiles: f32 = screen_height() / (t_b_size);
        let s_width_in_tiles: f32 = screen_width() / (t_b_size);

        for x in -2..(s_width_in_tiles+2.) as i32 {
            for y in -2..(s_height_in_tiles+2.) as i32 {
                draw_text(
                    self.get(x - (render_offset.x / t_b_size) as i32, y - (render_offset.y / t_b_size) as i32).to_string(),
                    x as f32 * t_b_size + (render_offset.x % t_b_size),
                    y as f32 * t_b_size + (render_offset.y % t_b_size),
                    self.tile_size,
                    WHITE
                );
            }
        }
    }
}

//----------------------------------------------Rule Implementing---------------------------------------------------
impl Board {
    pub fn iter(&mut self) {
        // make buffer
        let mut buffer = self.data.clone();

        //this system could be improved by converting tile_to_check to a struct-level system which is updated rather than recalced each frame

        // number of points within the current data * size of points & int to store * average number of tiles to check per tile in data
        let mut tiles_to_check: HashMap<Point<i32>, (bool, i32)> = HashMap::with_capacity(self.data.len() * (size_of::<i32>() + size_of::<Point<i32>>()) * 4);

        // check every living tile
        for living_tile in buffer.keys() {
            // add adjacent non-living tiles to be checked
            for offset in self.neighborhood {
                // tiles_to_check.insert(*living_tile + offset);
                // add tile to checked, and increment it's count of living neighbors, because thats how we got here
                tiles_to_check.entry(*living_tile + offset).or_insert(((offset.x == 0 && offset.y == 0), 0)).1 += 1;
            }
        }

        for (tile, (is_alive, neighbors)) in tiles_to_check {
            if is_alive {
                if neighbors != 3 && neighbors != 4 { // will include self, so up check by 1
                    self.set(tile, false);
                    // *buffer.get_mut(&tile).unwrap() = false;
                }
            } else {
                if neighbors == 3 {
                    self.set(tile, true);
                    // *buffer.get_mut(&tile).unwrap() = false;
                }
            }
        }
    }
}