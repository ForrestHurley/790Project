
#include "generate_halton_points.h"
#include "halton.h"

Coordinate GenerateHaltonPoints::operator()()
{
    double* quasi_random = new double[dimension];
    quasi_random = halton(seed, dimension);
    seed++;

    std::vector<double> quasi_vect(quasi_random, quasi_random + dimension);
    delete quasi_random;
    return Coordinate(quasi_vect);
}

void GenerateHaltonPoints::Reset(double new_seed)
{
    if (new_seed < 0)
    {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 10000);
        new_seed = dist(rd);
    }
    seed = new_seed;
}
