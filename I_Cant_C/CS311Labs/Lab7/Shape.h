#include <string>
#include <iostream>
using namespace std;

#pragma once
class Shape {
    protected:
        string background;
    public:
        string getBackground() const;
        void setBackground(string newVal);
        virtual void draw() const=0;
};