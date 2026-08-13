// use macroquad::prelude::*;

// pub mod maths;

// pub mod board;
// use crate::{board::Board, gui::GUI};

// pub mod gui;

// trait Renderable {
//     fn render(&self);
// }

// enum UpdateMode {
//     Menu,
//     Game,
//     Pause
// }

// struct Game {
//     update_mode:UpdateMode,
//     board: Board,
//     camera_pos: Vec2,
//     gui: GUI
// }

// impl Game {
//     fn new() -> Self {
//         Game {
//             update_mode: UpdateMode::Menu,
//             board: Board::new(),
//             camera_pos: Vec2::ZERO,
//             gui: GUI::new()
//         }
//     }

//     pub fn init(&mut self) {
//         self.gui.new_incrementable("thing: ", "",0., 0.5, -60., -110., 50., 100., PURPLE, BLACK);
//     }

//     async fn menu_update(&mut self) {
//         if is_key_pressed(KeyCode::Space) {
//             self.update_mode = UpdateMode::Game;
//         }

//         draw_text("Press Space to Start", screen_width()/4., screen_height()/4., 40., WHITE);
//     }

//     async fn game_update(&mut self) {
//         clear_background(GRAY);

//         if is_key_pressed(KeyCode::Escape) {
//             self.update_mode = UpdateMode::Pause;
//         }
//         for key in get_keys_down() {
//             match key {
//                 KeyCode::W=>{self.camera_pos.y -= 1.},
//                 KeyCode::A=>{self.camera_pos.x -= 1.},
//                 KeyCode::S=>{self.camera_pos.y += 1.},
//                 KeyCode::D=>{self.camera_pos.x += 1.},
//                 _=>{}
//             }
//         }
//         if is_mouse_button_down(MouseButton::Left) {
//             self.gui.check_click(mouse_position());
//         }

        

//         self.board.render(&self.camera_pos);
//         // self.board.debug_render(&self.camera_pos);
//         // draw_text("test", 10., 100., 64., BLUE);
//         self.gui.render();
//     }

//     async fn pause_update(&mut self) {
//         if is_key_pressed(KeyCode::Escape) {
//             self.update_mode = UpdateMode::Game;
//         }
//     }
// }

// #[macroquad::main("Cellular Automota")]
// async fn main() {
//     /*----------Inits----------*/
//     let mut game = Game::new();

//     game.init();

//     game.gui.new_text_item(screen_dpi_scale().to_string(), -100., -100., 30., PURPLE);

//     game.board.rand_fill();
    
//     /*----------Loops----------*/
//     loop {

//         match game.update_mode {
//             UpdateMode::Menu => { game.menu_update().await},
//             UpdateMode::Game => { game.game_update().await},
//             UpdateMode::Pause => { game.pause_update().await}
//         }

//         next_frame().await
//     }
// }
