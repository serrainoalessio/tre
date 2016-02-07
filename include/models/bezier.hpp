#ifndef BEZIER_MODEL_HPP
#define BEZIER_MODEL_HPP

#include <vector>
#include "image/image.hpp"
#include "misc.hpp"


using namespace std;

class Bezier{
public:
    uint* generatorsIndexes;
    Point2D* generators;
    Point2D* generatorsNew;

    Point2D* samples;

    const uint generatorCount,sampleCount;

    Image W,W_inv,Gen,GenN,Samples;


    Bezier(uint gc,uint sc,uint* indexes);

    void setGenerators(vector<Point2D>& points);

    void computeSamples();
    void computeGenerators();

    void draw(Image& img);
};

#endif
