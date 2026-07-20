use three_d::*;

pub struct Particle {
    center: Vector2<f32>,
    radius: f32,
    color: Srgba,
    geom_circle: Circle
}

impl Particle {
    fn new(x:f32, y:f32, r:f32, color:Srgba, context:&Context) -> Self {
        Self {center: vec2(x, y), radius:r, color:color, geom_circle:Circle::new(context, (x, y), r)}
    }
}