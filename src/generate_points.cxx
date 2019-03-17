#include "generate_points.h"

std::vector<Coordinate> *GeneratePoints::CreateNPoints(int number)
{
    std::vector<Coordinate>* points = new std::vector<Coordinate>();
    points->reserve(number);

    for (int i = 0; i < number; i++)
    {
        //Call the operator() function on this object
        //Should probably avoid writing things which look like this in the future
        //It is not very readable
        points->push_back((*this)());
    }

    return points;
}
