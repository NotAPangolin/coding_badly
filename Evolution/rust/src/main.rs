// Entry point for non-wasm
#[cfg(not(target_arch = "wasm32"))]
#[tokio::main]
async fn main() {
    run().await;
}

use three_d::*;

pub mod particle;

pub async fn run() {
    // Context Setup
    let window = Window::new(WindowSettings {
        title: "Simulation".to_string(),
        min_size: (100,100), max_size: Some((1920,1080)), initial_size: Some((1280,720)),
        borderless: false,
        ..Default::default()
    }).unwrap();
    let gl_context = window.gl();
    let scale_factor = window.device_pixel_ratio();
    let (width, height) = (window.size().0 as f32, window.size().1 as f32);

    // Test Renderables Setup
    let mut circle = Gm::new(
        Circle::new(
            &gl_context,
            vec2(width/3., height/2.),
            width/10.
        ),
        ColorMaterial {
            color: Srgba::new(0, 255, 255, 128),
            is_transparent: true,
            ..Default::default()
        }
    );

    // Run
    window.render_loop(move |frame_input| {
        frame_input
            .screen()
            .clear(ClearState::color_and_depth(0.1, 0.1, 0.1, 1., 1.))
            .render(
                Camera::new_2d(frame_input.viewport),
                circle.into_iter(),
                &[]
            );
        
        FrameOutput::default()
    });
}