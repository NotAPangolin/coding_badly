#include "Shape.h"

#pragma once
class Rectangle: public Shape  {
    private:
        int width;
        int height;
    public:
        Rectangle();
        Rectangle(int w, int h, string bg);
        void draw() const override;
        int getArea();
};