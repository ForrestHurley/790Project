#ifndef RADIAL_DISTRIBUTION_H
#define RADIAL_DISTRIBUTION_H

#include "coordinate.h"
#include <vector>

class RadialDistribution
{
public:
    int iterations = 1 << 20;
    double r_step = 0.05;
    std::vector<double> CalculateDistribution(
            const std::vector<Coordinate> &points, const Coordinate& range);
};

#endif
