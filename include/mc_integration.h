#ifndef MC_INTEGRATION_H
#define MC_INTEGRATION_H

#include "coordinate.h"
#include <vector>
#include <tuple>

class IntegrableFunction {
public:
    virtual double operator()(const Coordinate& point) const = 0;
};

class IntegrablePi : public IntegrableFunction {
public:
    double operator()(const Coordinate& point) const override;

    static double EstimatePi(double unit_square_integral, int dimension);
};

class IntegrableNormal : public IntegrableFunction {
public:
    double operator()(const Coordinate& point) const override;
};

class MonteCarloIntegration
{
public:
    const IntegrableFunction& foo;

    MonteCarloIntegration(const IntegrableFunction& foo) :
        foo(foo) {}

    std::tuple<double, double> IntegrateWithPoints(
            const std::vector<Coordinate>& points);
};

#endif
