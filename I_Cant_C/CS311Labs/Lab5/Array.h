#include <cstddef> // for size_t

class Array {
    private:
        int* arr;
        int size;
    public:
        explicit Array(int size); // construct
        Array(const Array &originArray); // copy
        ~Array(); // destruct

        //assignment?/retrieval operator to make debugging/testing reasonable
        int& operator[](size_t index) const;
};