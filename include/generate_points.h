#ifndef GENERATE_POINTS_H
#define GENERATE_POINTS_H

#include "coordinate.h"

class GeneratePoints
{
public:
    const int dimension;

    GeneratePoints(int dimension) :
        dimension(dimension) {}

    virtual Coordinate operator()() = 0;
    virtual std::vector<Coordinate> *CreateNPoints(int number);

    virtual void Reset(double seed) = 0;
};

#endif
