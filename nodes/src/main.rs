use macroquad::prelude::*;

pub mod point_manager;
use crate::point_manager::{Point, PointManager};


#[macroquad::main("Node-ing off")]
async fn main() {
    // Init Code
    let mut point_mngr = PointManager::new();

    let mut cam_pos: Vec2 = Vec2 { x: 0., y: 0. };
    

    // Loops
    loop {
        clear_background(Color { r: 0.8, g: 0.8, b: 0.8, a: 1.0 });

        if is_mouse_button_pressed(MouseButton::Left) {
            point_mngr.add_point(Point::new(mouse_position().0+cam_pos.x, mouse_position().1+cam_pos.y, 10.0, Color { r: 0., g: 0.6, b: 0.7, a: 0.8 }));
        }
        for key in get_keys_down() {
            match key {
                KeyCode::W=>{cam_pos.y -= 1.},
                KeyCode::A=>{cam_pos.x -= 1.},
                KeyCode::S=>{cam_pos.y += 1.},
                KeyCode::D=>{cam_pos.x += 1.},
                _=>{}
            }
        }

        point_mngr.render(cam_pos);

        next_frame().await
    }
}
