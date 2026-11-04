#include "Shape.h"
#include <iostream>


string Shape::getBackground() const {
    return background;
}
void Shape::setBackground(string newVal) {
    background = newVal;
}