#include "radial_distribution.h"

#include <random>
#include "xorshift.h"

std::vector<double> RadialDistribution::CalculateDistribution(
        const std::vector<Coordinate> &points, const Coordinate& range)
{
    std::uniform_int_distribution<int> int_dist(0,points.size()-1);
    xorshift prng;
    prng.reseed();
    const int max_count = range.getMagnitude() / 2. / r_step + 1;
    std::vector<int> counts(max_count,0);

    for (int i = 0; i < iterations; i++)
    {
        double dist =
            Coordinate::FlatTorusDisplacement(
                points.at(int_dist(prng)),
                points.at(int_dist(prng)),
                range)
            .getMagnitude();
        counts.at((int)(dist/r_step)) += 1;
    }

    std::vector<double> densities(counts.size(),0.);
    for (int i = 0; i < counts.size(); i++)
    {
        densities[i] = (double)counts[i] / (double)iterations / 
            (double)(std::pow(r_step * (i + 0.5),range.dimension - 1) * r_step);
    }

    return densities;
}
