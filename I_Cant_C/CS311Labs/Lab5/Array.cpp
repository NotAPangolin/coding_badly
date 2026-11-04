#include "Array.h"

Array::Array(int size) : size{size} {
    arr = new int[size];
}
Array::Array(const Array &originArray) {
    size = originArray.size;

    arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = originArray.arr[i];
    }
}
Array::~Array() {
    delete[] arr;
}

// assignment/retrieval operator
int& Array::operator[](size_t index) const {
    return arr[index];
}