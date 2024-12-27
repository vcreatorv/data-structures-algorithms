// Point.h
#ifndef POINT_H
#define POINT_H

#include <cmath>

class Point 
{
public:
    Point(double x = 0, double y = 0);
    double getX() const;
    double getY() const;
    double distanceTo(const Point& other) const;

private:
    double x, y;
};

#endif // POINT_H