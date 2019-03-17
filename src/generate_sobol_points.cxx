
#include "generate_sobol_points.h"
#include "sobol.h"

Coordinate GenerateSobolPoints::operator()()
{
    double *quasi_random = new double[dimension];
    i8_sobol(dimension, &seed, quasi_random);

    std::vector<double> quasi_vect(quasi_random, quasi_random + dimension);
    delete quasi_random;
    return Coordinate(quasi_vect);
}

void GenerateSobolPoints::Reset(double new_seed)
{
    if (new_seed < 0)
    {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 10000);
        new_seed = dist(rd);
    }
    seed = new_seed;
}
