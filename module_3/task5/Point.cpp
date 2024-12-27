// Point.cpp
#include "Point.h"

Point::Point(double x, double y) 
: x(x), y(y) 
{
}

double Point::getX() const { return x; }

double Point::getY() const { return y; }

double Point::distanceTo(const Point& other) const 
{
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}