// CS311Fall2025Lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>



int calculateWage(int baseSalary, int hourlyRate, int extraHours) {
    return (baseSalary + hourlyRate * extraHours);
}




int main()
{
    int baseSalary = 50'000;
    int hourlyRate = 20;
    int extraHours = 10;


    int wage = calculateWage(baseSalary, hourlyRate, extraHours);
    std::cout << "Wage: " << wage << std::endl;





    return 0;
}


