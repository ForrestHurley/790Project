
#include "xorshift.h"
#include "coordinate.h"
#include <random>
#include <iostream>
#include <algorithm>

#include "generate_points.h"
#include "generate_random_points.h"
#include "generate_sobol_points.h"
#include "generate_halton_points.h"

#include "mc_integration.h"
#include "radial_distribution.h"

double calc_mean(const std::vector<double>& values)
{
    double sum = std::accumulate(
        values.begin(), values.end(), 0.0);
    return sum / values.size();
}

double calc_var(const std::vector<double>& values)
{
    double mean = calc_mean(values);

    std::vector<double> diff(values.size());
    std::transform(
        values.begin(), values.end(), diff.begin(),
        [mean](double x) {return x - mean;});
    double sq_sum = std::inner_product(
        diff.begin(), diff.end(), diff.begin(), 0.0);
    return sq_sum / (values.size() - 1);
}

int main()
{
    int min_dimension = 2;
    int max_dimension = 20;
    int number_of_samples = 1000;
    int total_iterations = 100;

    std::cout << "Running " << total_iterations 
        << " iterations per dimension" << std::endl;
    
    for (int dim = min_dimension; dim <= max_dimension; dim++)
    {
        std::cout << "Starting dimension " << dim << std::endl;

        std::vector<double> rand_vect, sobol_vect, halton_vect;
        for (int iteration = 0; iteration < total_iterations; iteration++)
        {
            GenerateRandomPoints rand_gen(dim);
            GenerateSobolPoints sobol_gen(dim);
            GenerateHaltonPoints halton_gen(dim);

            rand_gen.Reset(-1);
            sobol_gen.Reset(-1);
            halton_gen.Reset(-1);

            std::vector<Coordinate>* random_points =
                rand_gen.CreateNPoints(number_of_samples);
            std::vector<Coordinate>* sobol_points =
                sobol_gen.CreateNPoints(number_of_samples);
            std::vector<Coordinate>* halton_points =
                halton_gen.CreateNPoints(number_of_samples);

            IntegrablePi pi_func;
            MonteCarloIntegration mc_integrator(pi_func);

            std::tuple<double, double> random_out = 
                mc_integrator.IntegrateWithPoints(*random_points);
            std::tuple<double, double> sobol_out = 
                mc_integrator.IntegrateWithPoints(*sobol_points);
            std::tuple<double, double> halton_out = 
                mc_integrator.IntegrateWithPoints(*halton_points);

            const double random_pi = IntegrablePi::EstimatePi(
                    std::get<0>(random_out), dim);
            const double sobol_pi = IntegrablePi::EstimatePi(
                    std::get<0>(sobol_out), dim);
            const double halton_pi = IntegrablePi::EstimatePi(
                    std::get<0>(halton_out), dim);

            rand_vect.push_back(random_pi);
            sobol_vect.push_back(sobol_pi);
            halton_vect.push_back(halton_pi);

            delete random_points;
            delete sobol_points;
            delete halton_points;
        }

        double mean_rand = calc_mean(rand_vect);
        double mean_sobol = calc_mean(sobol_vect);
        double mean_halton = calc_mean(halton_vect);

        double var_rand = calc_var(rand_vect);
        double var_sobol = calc_var(sobol_vect);
        double var_halton = calc_var(halton_vect);

        std::cout << "Calculated pi values:" << std::endl;
        std::cout << "Mean | Variance" << std::endl;
        std::cout << mean_rand << " | " << var_rand << std::endl;
        std::cout << mean_sobol << " | " << var_sobol << std::endl;
        std::cout << mean_halton << " | " << var_halton << std::endl;
    }
    return 0;
}
