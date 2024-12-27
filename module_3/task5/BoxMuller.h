// BoxMuller.h
#ifndef BOX_MULLER_H
#define BOX_MULLER_H
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include "Point.h"

class BoxMuller 
{
public:
    static Point generatePoint(double mean = 0, double stddev = 1);
};

#endif // BOX_MULLER_H