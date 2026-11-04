#include "Rectangle.h"


Rectangle::Rectangle(): width(1), height(1) {background = "default";}
Rectangle::Rectangle(int w, int h, string bg): width(w), height(h) {background = bg;}
void Rectangle::draw() const {
    cout << "Drawing Rectangle with dims width=" << width << " & height=" << height << "\nbackground is '" << background << "'" << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << "+";
        }
        cout << endl;
    }
    cout << endl;
}
int Rectangle::getArea() {return width * height;}
