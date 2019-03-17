#ifndef GENERATE_MOLDYN_POINTS_H
#define GENERATE_MOLDYN_POINTS_H

#include "generate_points.h"

class GenerateMolDynPoints : public GeneratePoints
{
private:
    int iterations;
    double s; 
    double average_force_neighbors;
    double delta_t;

public:
    GenerateMolDynPoints(
            int dimension, int iterations = 1000,
            double s = 1, double average_force_neighbors = 10,
            double delta_t = 0.001) :
        GeneratePoints(dimension), iterations(iterations), 
        s(s), average_force_neighbors(average_force_neighbors),
        delta_t(delta_t) {}

    Coordinate operator()() override { return Coordinate(dimension); }
    virtual std::vector<Coordinate> *operator()(int number);
    
    void Reset(double seed) override {} 
};

#endif
