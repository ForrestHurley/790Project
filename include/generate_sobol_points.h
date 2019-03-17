#ifndef GENERATE_SOBOL_POINTS_H
#define GENERATE_SOBOL_POINTS_H

#include "generate_points.h"

class GenerateSobolPoints : public GeneratePoints
{
private:
    long long int seed;
public:
    GenerateSobolPoints(int dimension) :
        GeneratePoints(dimension), seed(0) {}

    Coordinate operator()() override;
    
    void Reset(double seed) override; 
};

#endif
