#include "ArrayNew.h"

using namespace std;

ArrayNew::ArrayNew(int size_) : size(size_) {
    arr = unique_ptr<int[]> (new int[size]);
}

ArrayNew::ArrayNew(const ArrayNew &originArray) {
    size = originArray.size;

    arr = unique_ptr<int[]> (new int[size]);
    for (int i = 0; i < size; i++) {
        arr[i] = originArray.arr[i];
    }
}

// assignment/retrieval operator
int& ArrayNew::operator[](size_t index) const {
    return arr[index];
}