#include "mc_integration.h"

#include <numeric>
#include <algorithm>
#include <cmath>

double factorial(double x) {return std::tgamma(x+1);}

double IntegrablePi::operator()(const Coordinate& point) const
{
    return (double)(int)(point.getMagnitudeSquared() <= 1);
}

double IntegrablePi::EstimatePi(double unit_square_integral, int dimension)
{
    const double volume = std::pow(2., dimension) * unit_square_integral;

    if (dimension % 2 == 0)
    {
        const int k = dimension / 2;
        const double pi_power = volume * factorial(k);
        return std::pow(pi_power, 1. / k);
    }
    else
    {
        const int k = ( dimension - 1 ) / 2;
        const double pi_power = volume * factorial(2. * k + 1) 
            / 2. / factorial(k);
        return 0.25 * std::pow(pi_power, 1. / k);
    }
}

double IntegrableNormal::operator()(const Coordinate& point) const
{
    return Coordinate::Pow(2.71828182845904523536,point * point * -1).getMagnitudeSquared();
}

std::tuple<double, double>
MonteCarloIntegration::IntegrateWithPoints(
        const std::vector<Coordinate>& points)
{
    std::vector<double> sample_values;
    sample_values.reserve(points.size());
    for (Coordinate point : points)
        sample_values.push_back(foo(point));

    double sum = std::accumulate(
        sample_values.begin(), sample_values.end(), 0.0);
    double mean = sum / sample_values.size();

    std::vector<double> diff(sample_values.size());
    std::transform(
        sample_values.begin(), sample_values.end(), diff.begin(),
        [mean](double x) {return x - mean;});
    double sq_sum = std::inner_product(
        diff.begin(), diff.end(), diff.begin(), 0.0);
    double var = sq_sum / (sample_values.size() - 1);

    return std::make_tuple(mean, var);
}
