#ifndef BEZIER_MODEL_HPP
#define BEZIER_MODEL_HPP

#include <vector>
#include "image/image.hpp"

using namespace std;

class Bezier{
public:

    vector<Point2D> generators;
    vector<Point2D> points;

    Image W,W_inv,B,C;

    Bezier(int generatorCount,int sampleCount);

    void computePoints();
    void computeGenerators();
};

#endif
