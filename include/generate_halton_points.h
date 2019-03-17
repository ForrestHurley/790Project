#ifndef GENERATE_HALTON_POINTS_H
#define GENERATE_HALTON_POINTS_H

#include "generate_points.h"

class GenerateHaltonPoints : public GeneratePoints
{
private:
    int seed;        
public:
    GenerateHaltonPoints(int dimension) :
        GeneratePoints(dimension), seed(0) {}

    Coordinate operator()() override;
    
    void Reset(double seed) override; 
};

#endif
