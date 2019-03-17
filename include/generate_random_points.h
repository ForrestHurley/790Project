#ifndef GENERATE_RANDOM_POINTS_H
#define GENERATE_RANDOM_POINTS_H

#include "generate_points.h"
#include "xorshift.h"

class GenerateRandomPoints : public GeneratePoints 
{
private:
    xorshift random_generator;
public:
    GenerateRandomPoints(int dimension) :
        GeneratePoints(dimension), random_generator() {}

    Coordinate operator()() override;

    void Reset(double seed) override;
};

#endif
