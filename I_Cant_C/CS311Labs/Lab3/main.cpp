#include <iostream>
#include <string>

#include <C:\Users\bmcca\GitHub\coding_badly\I_Cant_C\CS311Labs\Lab2\TextBox.cpp>

using namespace std;

/* Requirements:

For lab 3, you need to
-present your solution to our teaching assistant, and
-submit your .h and .cpp files to the blackboard.
Question:


1. Create a TextBox class by implementing the UML
- *see image*
- You need to get the information about this class from this UML(like data variables and member
functions).

UML interpretation:
- private val: [value: string]
- public methods:
    - TextBox() <- initializer
    - TextBox(val: string) <- (overload) initializer
    - ~TextBox() <- package??

    - getValue():string
    - setValue(val:string)

2. According to this class you created, in the main function of your main.cpp file
- create two instances of TextBox class, and run the program.

3. Show the TextBox class and explain to your teaching assistant step by step.

*/

int main() {
    TextBox t1;
    t1.setValue("This is Box 1");

    TextBox t2("This is Box 2");

    cout << "Box 1 text: '" << t1.getValue() << "'" << endl;
    cout << "Box 2 text: '" << t2.getValue() << "'" << endl;

    return 0;
}