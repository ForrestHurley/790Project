#ifndef GENERATE_GRID_POINTS_H
#define GENERATE_GRID_POINTS_H

#include "generate_points.h"

class GenerateGridPoints : public GeneratePoints 
{
public:
    int side_count;

    GenerateGridPoints(int dimension, int side_count = 4) :
        GeneratePoints(dimension), side_count(side_count) {}

    Coordinate operator()() override { return Coordinate(dimension); }
    std::vector<Coordinate>* CreateNPoints(int number) override;

    void Reset(double seed) override {}
};

#endif
