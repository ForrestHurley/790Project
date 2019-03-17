
#include "generate_moldyn_points.h"

#include "generate_random_points.h"
#include "KDTree.h"

std::vector<Coordinate> *GenerateMolDynPoints::operator()(int number)
{
    GenerateRandomPoints random_gen = GenerateRandomPoints(dimension);
    std::vector<Coordinate>* distributed_points = random_gen.CreateNPoints(number);

    /*double radius = ;

    for (int i = 0; i < iterations; i++)
    {
        KDTree neighbor_tree = KDTree(*random_points);

        for (Coordinate& coord : distributed_points)
        {
            std::vector<Coordinate> neighbors = neighbor_tree.neighborhood_points(coord, radius);
        
            for (Coordinate& other_coord : neighbors)
            {

            }
        }
    }*/

    return distributed_points;
}

