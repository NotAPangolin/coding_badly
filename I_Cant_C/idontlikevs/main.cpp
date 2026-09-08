#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isLeapYear(int year) {
    if (year % 400 == 0) { return true; }
    if (year % 100 == 0) { return false; }
    if (year % 4 == 0) { return true; }
    else { return false; }

    // or

    return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
}

int linearSearch(int arr[], int arrlen, int val) {
    // linear search algorithim in O(n) time (best case O(1), worst case O(n))
    // checks each item against given value

    // int arrlen = size(arr);
    // cout << size;
    int found_index = -1;
    for (int i = 0; i < arrlen; i++) {
        if (arr[i] == val) {
            found_index = i;
            break;
        }
    }
    return found_index;
}

int main()
{
    // vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

    // for (const string& word : msg)
    // {
    //     cout << word << " ";
    // }
    // cout << endl;



    // int year;

    // cin >> year;

    // cout << isLeapYear(year);



    int arr[5] = {5,4,3,2,1};
    // cout << sizeof(arr) << " " << size(arr) << " " << sizeof(arr)/sizeof(int) << endl;
    cout << linearSearch(arr, size(arr), 2) << endl; // should be 3
    cout << linearSearch(arr, size(arr), 5) << endl; // should be 0
    cout << linearSearch(arr, size(arr), 9) << endl; // should be -1



    return 0;
}
