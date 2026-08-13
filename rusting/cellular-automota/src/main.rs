use macroquad::{input::KeyCode::{Escape, LeftAlt}, prelude::*};

pub mod maths;

pub mod board;
use crate::{board::Board, gui::GUI};

pub mod gui;

trait ScreenRenderable {
    fn render(&self);
    fn debug_render(&self) {} //optional
}
trait CameraRenderable {
    fn render(&self, render_offset: &Vec2);
    fn debug_render(&self, render_offset: &Vec2) {} //optional
}

enum UpdateMode {
    Menu,
    Game,
    Pause
}

#[macroquad::main("Cellular Automota")]
async fn main() {
    /*----------Inits----------*/
    let mut update_mode = UpdateMode::Game;
    let mut board = Board::new();
    let mut camera_pos = Vec2::ZERO;
    let mut gui = GUI::new();

    let mut running = false;
    let mut debugging = false;

    // gui.new_fetched_text_item(|| {&board.get_population().to_string()}, "pop: ", "", -150., 100., 10., BLUE);
    
    let mut pop_label = gui.new_text_item("pop: 0".to_string(),  -150., 100., 10., BLUE);

    // gui.new_incrementable("thing: ", "",0., 0.5, -60., -110., 50., 100., PURPLE, BLACK);

    board.rand_fill(10);


    /*----------Update Functions----------*/
    let mut menu_update = || {
        draw_text("Press Space to Start", screen_width()/4., screen_height()/4., 40., WHITE);
    };

    let mut game_update = || {
        // clear background
        clear_background(GRAY);

        // keybinds
        let alt_is_down = is_key_down(LeftAlt);

        for key in get_keys_down() {
            match key {
                KeyCode::W=>{camera_pos.y += 1.},
                KeyCode::A=>{camera_pos.x += 1.},
                KeyCode::S=>{camera_pos.y -= 1.},
                KeyCode::D=>{camera_pos.x -= 1.},
                _=>{}
            }
        }
        for key in get_keys_pressed() {
            match key {
                KeyCode::R => {board.clear(); camera_pos = Vec2::ZERO},
                KeyCode::Right => {board.iter()},
                KeyCode::Space => {running = !running},
                KeyCode::D => {if alt_is_down {debugging = !debugging}},
                _=>{}
            }
        }
        // Left mouse Press
        if is_mouse_button_pressed(MouseButton::Left) {
            gui.check_click(mouse_position());
        }
        // Right mouse Press
        // if is_mouse_button_pressed(MouseButton::Right) {
        // }
        // Left mouse Down
        if is_mouse_button_down(MouseButton::Left) {
            if alt_is_down {
                gui.check_click(mouse_position());
            }
            board.set(board.screen_to_tile((mouse_position().0 - camera_pos.x, mouse_position().1 - camera_pos.y)), true);
        }
        // Right mouse Down
        if is_mouse_button_down(MouseButton::Right) {
            // if alt_is_down {
            // }
            board.set(board.screen_to_tile(mouse_position()), false);
        }

        // run sim
        if running {
            board.iter();
        }

        // render
        board.render(&camera_pos);        

        if debugging {
            board.debug_render(&camera_pos);
        }

        // update labels
        pop_label.set_text("pop: 0".to_string() + &board.get_population().to_string());

        gui.render();

    };
    
    let mut pause_update = || {
    };
    
    /*----------Loops----------*/
    loop {
        // Handle mode changing
        if is_key_pressed(Escape) {
            match update_mode {
                UpdateMode::Menu => { update_mode = UpdateMode::Game},
                UpdateMode::Game => { update_mode = UpdateMode::Pause},
                UpdateMode::Pause => { update_mode = UpdateMode::Game}
            }
        }

        match update_mode {
            UpdateMode::Menu => { menu_update()},
            UpdateMode::Game => { game_update()},
            UpdateMode::Pause => { pause_update()}
        }

        next_frame().await
    }
}
