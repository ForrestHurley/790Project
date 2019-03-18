
#include "generate_grid_points.h"

std::vector<Coordinate>* GenerateGridPoints::CreateNPoints(int number)
{
    std::vector<Coordinate>* out_vect = new std::vector<Coordinate>();
    out_vect->reserve(std::pow(side_count,dimension));

    std::vector<double> temp_coord(dimension, 0.);
    out_vect->push_back(temp_coord);

    assert(side_count > 1);
    const double dim_step = 1. / (side_count - 1.);
    const double end_point = 1. - 0.5 * dim_step;

    int current_dim = 0;
    while (current_dim < dimension)
    {
        if (temp_coord.at(current_dim) < end_point)
            temp_coord.at(current_dim) += dim_step;
        else
        {
            temp_coord.at(current_dim) = 0;
            current_dim += 1;
            continue;
        }

        out_vect->push_back(Coordinate(temp_coord));

        current_dim = 0;
    }

    return out_vect;
}
