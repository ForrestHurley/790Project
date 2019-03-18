
#include "xorshift.h"
#include "coordinate.h"
#include <random>
#include <iostream>
#include <algorithm>

#include "generate_points.h"
#include "generate_random_points.h"
#include "generate_sobol_points.h"
#include "generate_halton_points.h"
#include "generate_grid_points.h"

#include "mc_integration.h"
#include "radial_distribution.h"

double calc_mean(const std::vector<double>& values)
{
    double sum = std::accumulate(
        values.begin(), values.end(), 0.0);
    return sum / values.size();
}

double calc_var(const std::vector<double>& values, double mean)
{
    std::vector<double> diff(values.size());
    std::transform(
        values.begin(), values.end(), diff.begin(),
        [mean](double x) {return x - mean;});
    double sq_sum = std::inner_product(
        diff.begin(), diff.end(), diff.begin(), 0.0);
    return sq_sum / (values.size() - 1);
}

template<class GeneratePointsType>
void pi_integration(int number_of_samples = 2000)
{
    int min_dimension = 2;
    int max_dimension = 12;
    int total_iterations = 1000;

    //std::cout << "Running " << total_iterations 
    //    << " iterations per dimension with " <<
    //    number_of_samples << " samples" << std::endl;
    std::cout << "Dimension, Mean, Variance" << std::endl;
    
    for (int dim = min_dimension; dim <= max_dimension; dim++)
    {
        std::vector<double> val_vect;
        for (int iteration = 0; iteration < total_iterations; iteration++)
        {
            GeneratePointsType point_gen(dim);
            point_gen.Reset(-1);

            std::vector<Coordinate>* value_points =
                point_gen.CreateNPoints(number_of_samples);

            IntegrablePi pi_func;
            MonteCarloIntegration mc_integrator(pi_func);

            std::tuple<double, double> value_out = 
                mc_integrator.IntegrateWithPoints(*value_points);

            const double value_pi = IntegrablePi::EstimatePi(
                    std::get<0>(value_out), dim);

            val_vect.push_back(value_pi);

            delete value_points;
        }

        double mean_val = calc_mean(val_vect);

        const double pi = 3.14159265359;
        double var_val = calc_var(val_vect, pi);

        std::cout << dim << ", " << mean_val << ", " << var_val << std::endl;
    }
}

template<class GeneratePointsType>
void radial_calculation(int dim, int number_of_samples = 1000000, int number_of_iterations = 2500000, int side_count = -1)
{
    RadialDistribution dist_calc;
    dist_calc.iterations = number_of_iterations;
    dist_calc.r_step = 0.005;

    GeneratePointsType point_gen(dim);
    point_gen.Reset(-1);

    std::vector<Coordinate>* value_points =
        point_gen.CreateNPoints(number_of_samples);

    std::vector<double> dist_values = dist_calc.CalculateDistribution(
            *value_points, Coordinate(std::vector<double>(dim,1.)));

    std::cout << "Radius, Density" << std::endl;
    for (int i = 0; i < dist_values.size(); i++)
        std::cout << i * dist_calc.r_step << ", " << dist_values.at(i) << std::endl;
}


template<>
void radial_calculation<GenerateGridPoints>(
        int dim, int number_of_samples, 
        int number_of_iterations, int side_count)
{
    RadialDistribution dist_calc;
    dist_calc.iterations = number_of_iterations;
    dist_calc.r_step = 0.005;

    if (side_count <= 0)
        side_count = 4;

    GenerateGridPoints point_gen(dim, side_count);
    point_gen.Reset(-1);

    std::vector<Coordinate>* value_points =
        point_gen.CreateNPoints(number_of_samples);

    std::vector<double> dist_values = dist_calc.CalculateDistribution(
            *value_points, Coordinate(std::vector<double>(dim,1.)));

    std::cout << "Radius, Density" << std::endl;
    for (int i = 0; i < dist_values.size(); i++)
        std::cout << i * dist_calc.r_step << ", " << dist_values.at(i) << std::endl;
}

int main()
{
    //pi_integration<GenerateRandomPoints>();
    //pi_integration<GenerateSobolPoints>();
    //pi_integration<GenerateHaltonPoints>();
    
    radial_calculation<GenerateRandomPoints>(2);
    radial_calculation<GenerateRandomPoints>(6);
    radial_calculation<GenerateSobolPoints>(2);
    radial_calculation<GenerateSobolPoints>(6);
    radial_calculation<GenerateHaltonPoints>(2);
    radial_calculation<GenerateHaltonPoints>(6); 
    radial_calculation<GenerateGridPoints>(2,1000000,2500000,1000);
    radial_calculation<GenerateGridPoints>(6,1000000,2500000,10);

    return 0;
}
