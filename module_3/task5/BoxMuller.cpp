// BoxMuller.cpp
#include "BoxMuller.h"

Point BoxMuller::generatePoint(double mean, double stddev) 
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(0.0, 1.0);

    double u1 = dis(gen);
    double u2 = dis(gen);

    double z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2 * M_PI * u2);
    double z1 = std::sqrt(-2.0 * std::log(u1)) * std::sin(2 * M_PI * u2);

    return Point(mean + stddev * z0, mean + stddev * z1);
}