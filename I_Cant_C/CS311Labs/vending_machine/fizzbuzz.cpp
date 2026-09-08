#include <iostream>
#include <string>

using namespace std;


string fizzbuzz(int in) {
    string output;
    if (in % 3 == 0) {output += "Fizz";}
    if (in % 5 == 0) {output += "Buzz";}
    if (output == "") {cout << in << endl;}
    cout << output << endl;
    return output;
}

int main() {
    fizzbuzz(15);
    fizzbuzz(2);
}