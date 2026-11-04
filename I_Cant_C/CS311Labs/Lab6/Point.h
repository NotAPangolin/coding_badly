#include <iostream>
using namespace std;

class Point {
    private:
        int x;
        int y;
    public:
        Point(int x_, int y_);

        //Equality Operators
        bool operator==(const Point& pnt) const;
        bool operator!=(const Point& pnt) const;
        //Comparison Operators
        bool operator>(const Point& pnt) const;
        bool operator<(const Point& pnt) const;
        bool operator>=(const Point& pnt) const;
        bool operator<=(const Point& pnt) const;
        //Insertion Operator (as friend)
        friend ostream& operator<<(ostream& out, const Point& pnt);
        //Arithmetic operators w/ ints
        Point operator+(int val) const;
        Point& operator+=(int val);
        //Arithmetic Operators w/ points
        Point operator+(const Point& pnt) const;
        Point operator-(const Point& pnt) const;
        Point operator*(const Point& pnt) const;
        Point operator/(const Point& pnt) const;

        Point& operator+=(const Point& pnt);
        Point& operator-=(const Point& pnt);
        Point& operator*=(const Point& pnt);
        Point& operator/=(const Point& pnt);
        //assignment operator
        Point& operator=(const Point& pnt);
};