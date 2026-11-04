/*
Question: Create an Array class according to the UML below:

----
Array
-arr: int*
-size: int

+Constructor: constructor with parameters
+Copy constructor:
+Destructor:

----
Then, create a new class: ArrayNew, use unique pointer to replace the raw pointer
you used before
*/

#include <iostream>
using namespace std;

#include "Array.cpp"
#include "ArrayNew.cpp"

int main() {
    Array arr1 = Array(5);
    for (int i = 0; i < 5; i ++) {
        arr1[i] = i;
    }
    cout << "arr1 def didn't crash!" << endl;

    ArrayNew arr2 = ArrayNew(5);
    for (int i = 0; i < 5; i ++) {
        arr2[i] = i+10;
    }
    cout << "arr2 def didn't crash!" << endl;

    cout << "arr1: ";
    for (int i = 0; i < 5; i ++) {
        cout << arr1[i] << " ";
    }
    cout << endl << "arr2: ";
    for (int i = 0; i < 5; i ++) {
        cout << arr2[i] << " ";
    }
}