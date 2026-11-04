#include "Point.h"

using namespace std;

Point::Point(int x_, int y_) : x(x_), y(y_) {}

//Equality Operators
bool Point::operator==(const Point& pnt) const {
    return ((x == pnt.x) && (y == pnt.y));
}
bool Point::operator!=(const Point& pnt) const {
    return ((x != pnt.x) || (y != pnt.y));
}
//Comparison Operators
bool Point::operator>(const Point& pnt) const {
    return ((x*x+y*y)>(pnt.x*pnt.x+pnt.y*pnt.y));
}
bool Point::operator<(const Point& pnt) const {
    return ((x*x+y*y)<(pnt.x*pnt.x+pnt.y*pnt.y));
}
bool Point::operator>=(const Point& pnt) const {
    return ((x*x+y*y)>=(pnt.x*pnt.x+pnt.y*pnt.y));
}
bool Point::operator<=(const Point& pnt) const {
    return ((x*x+y*y)<=(pnt.x*pnt.x+pnt.y*pnt.y));
}
//Insertion Operator (as global friend func)
ostream& operator<<(ostream& out, const Point& pnt) {
    out << "Point(" << pnt.x << ", " << pnt.y << ")";
    return out;
}
//Arithmetic operators w/ ints
Point Point::operator+(int val) const {
    return Point(x+val,y+val);
}
Point& Point::operator+=(int val) {
    x+=val;
    y+=val;
    return *this;
}
//Arithmetic Operators w/ points
Point Point::operator+(const Point& pnt) const {
    return Point(x+pnt.x,y+pnt.y);
}
Point Point::operator-(const Point& pnt) const {
    return Point(x-pnt.x,y-pnt.y);
}
Point Point::operator*(const Point& pnt) const {
    return Point(x*pnt.x,y*pnt.y);
}
Point Point::operator/(const Point& pnt) const {
    return Point(x/pnt.x,y/pnt.y);
}

Point& Point::operator+=(const Point& pnt) {
    x+=pnt.x;
    y+=pnt.y;
    return *this;
}
Point& Point::operator-=(const Point& pnt) {
    x-=pnt.x;
    y-=pnt.y;
    return *this;
}
Point& Point::operator*=(const Point& pnt) {
    x*=pnt.x;
    y*=pnt.y;
    return *this;
}
Point& Point::operator/=(const Point& pnt) {
    x/=pnt.x;
    y/=pnt.y;
    return *this;
}
//Compound assignment operator
Point& Point::operator=(const Point& pnt) {
    x=pnt.x;
    y=pnt.y;
    return *this;
}
