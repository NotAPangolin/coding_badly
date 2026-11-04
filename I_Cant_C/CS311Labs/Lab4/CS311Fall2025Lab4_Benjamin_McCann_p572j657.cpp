// CS311Fall2025Lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*
for the base program:
a) What is the output?
    - "Wage: 50200"
b) This program is written in procedural programming, what is the problem?
    - nothing, technically
    - it takes no input
    - to handle different inputs you have to manually edit code
        - its a lot of code
    - to do it multiple times (handle multiple employees) you have to rerun the entire program
c) Refactor this code by using Object-Oriented Programming.
    - Encapsulation
        - put the data and methods in an Employee class
    - abstraction
        - make data members private and provide public accessors
    - coupling
        - reduced by removal/reorganizing of Employee members
    -  dependancy, inheritance
        - shouldn't apply here
*/

#include <iostream>

#include "C:\Users\bmcca\GitHub\coding_badly\I_Cant_C\CS311Labs\Lab4\Employee.cpp"


int main()
{
    Employee emp1(50'000, 20);

    emp1.printWage("emp1", 10);

    return 0;
}


