/*
Question: A drawing application: the user can add different kinds of shapes to a canvas.
All these shapes have a few things in common, like background color, border and so on.
As your exercise,
- create a new class: Shape and let two classes: Rectangle and Circle derive from the Shape.
- For each class you should implement the member functions in the implementation file.
- Add a function to base class: draw(), let two derived classes override this function.
- Back to main file, create a function: showShape(), pass a Shape object as the argument, draw
shape for implementation.
- Use Polymorphic Collection: create a vector of Shape, put a rectangle and a circle to it, loop over
the vector draw a rectangle and a circle on the console. (use late or dynamic binding)
- Rewrite this code using unique pointer instead.


Shape
-background: string
+getBackground( )
+setBackground( )


Rectangle
-width: int
-heigth: int
+Rectangle( );
+Rectangle(int width, int height)
+void draw( );
+int getArea( );
*/
#include <string>
#include <iostream>
#include <vector>
#include <memory>

#include "Rectangle.cpp"
#include "Circle.cpp"

using namespace std;

void showShape(Shape& shape) {
    shape.draw();
}

int main() {
    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(unique_ptr<Shape> (new Rectangle(6,2, "gray")));
    shapes.push_back(unique_ptr<Shape> (new Circle(5, "red")));
    
    for (int i = 0; i < shapes.size(); i++) {
        cout << "\nShape " << i << ":" << endl;
        showShape(*shapes[i]);
    }
}