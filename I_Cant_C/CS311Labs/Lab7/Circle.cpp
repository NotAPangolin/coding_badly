#include "Circle.h"


Circle::Circle(): radius(1) {background = "default";}
Circle::Circle(int r, string bg): radius(r) {background = bg;}
void Circle::draw() const {
    cout << "Drawing Circle with dims radius=" << radius << "\nbackground is '" << background << "'" << endl;
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            if (i*i+j*j <= radius*radius) {
                cout << "[]";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}
int Circle::getArea() {return pi * radius * radius;}
