#include "generate_random_points.h"
#include <random>

Coordinate GenerateRandomPoints::operator()()
{
    std::vector<double> temp_points;
    temp_points.reserve(dimension);

    std::uniform_real_distribution<double> unif(0.,1.);
    for (int i = 0; i < dimension; i++)
        temp_points.push_back(unif(random_generator));

    return Coordinate(temp_points);
}

void GenerateRandomPoints::Reset(double seed)
{
    random_generator.reseed();
}
