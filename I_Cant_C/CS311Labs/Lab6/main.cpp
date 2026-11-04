/*
Create a Point class, implement Equality operator, Inequality operator, Comparison
operator(four), Insertion operator (make it as friend of Point class), Arithmetic operators and
Compound Assignment operator.
Show the Point class and explain to your teaching assistant step by step by using the four test
cases.
*/
#include <iostream>
using namespace std;

#include "Point.cpp"

int main()
{
    Point first{ 10, 20 };
    Point second{ 12, 21 };


    // test case 1:
    cout << "Test Case 1:\n";
    
    if (first == second) {
        cout << "equal";
    }
    else {
        cout << "not equal";
    }
    // output: "not equal"


    // test case 2:
    cout << "\n\nTest Case 2:\n";

    if (first < second) {
        cout << "first is less than second";
    } else {
        cout << "first is not less than second";
    }
    //output: "first is less than second"


    // test case 3:
    cout << "\n\nTest Case 3:\n";

    cout << "first: " << first << ", second: " << second;
    //output: "first: Point(10, 20), second: Point(12, 21)"


    // test case 4:
    cout << "\n\nTest Case 4:\n";

    cout << first + 50;
    second += 100;
    cout << " " << second;
    //output: "Point(60, 70) Point(112, 121)"


    return 0;
}
