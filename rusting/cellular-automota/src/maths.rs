use num_traits::Num;

#[derive(PartialEq, Eq, Hash, Clone, Copy)]
pub struct Point<T: Num> {
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

