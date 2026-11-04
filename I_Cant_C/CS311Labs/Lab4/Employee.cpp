#include "C:\Users\bmcca\GitHub\coding_badly\I_Cant_C\CS311Labs\Lab4\Employee.h"

#include <stdexcept>
#include <iostream>

using namespace std;

// Constructors
Employee::Employee() {
    baseSalary = 0;
    hourlyRate = 0;
}
Employee::Employee(int baseSalary, int hourlyRate) {
    this->setBaseSalary(baseSalary);
    this->setHourlyRate(hourlyRate);
}

// Accessors
void Employee::setBaseSalary(int val) {
    if (val < 0) {
        throw invalid_argument("base_salary");
    }
    baseSalary = val;
}
void Employee::setHourlyRate(int val) {
    if (val < 0) {
        throw invalid_argument("base_salary");
    }
    hourlyRate = val;
}

// removed since they are unnessecary in current code
// int Employee::getBaseSalary() { // Currently unneeded
//     return baseSalary;
// }
// int Employee::getHourlyRate() {
//     return hourlyRate;
// }

// Other Methods
int Employee::calculateWage(int extraHours) {
    return (baseSalary + hourlyRate * extraHours);
}

void Employee::printWage(const char* label, int extraHours) {
    cout << label << ": " << calculateWage(3) << endl;
}
