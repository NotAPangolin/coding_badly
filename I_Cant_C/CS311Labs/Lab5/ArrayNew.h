#include <memory>

class ArrayNew {
    private:
        std::unique_ptr<int[]> arr;
        int size;
    public:
        ArrayNew(int size_);
        ArrayNew(const ArrayNew &originArray);
        // destructor no longer needed with unique_ptr

        //assignment?/retrieval operator
        int& operator[](size_t index) const;
};