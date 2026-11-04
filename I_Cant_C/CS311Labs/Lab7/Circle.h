#include "Shape.h"

float pi = 3.14159;
#pragma once
class Circle: public Shape  {
    private:
        int radius;
    public:
        Circle();
        Circle(int r, string bg);
        void draw() const override;
        int getArea();
};