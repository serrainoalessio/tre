#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <iostream>
#include <fstream>

#include "image/image.hpp"
#include "image/transform.hpp"

#include "bezier.hpp"
#include "misc.hpp"
#include "geometry.hpp"


using namespace std;

class Model{
    vector<Point2D> points;
    vector<Bezier> curves;

    Point2D* forces;
    int* forcesCount;

public:

    Model(string path);

    void computeSamples();
    void apply(const ImageTransform& t);

    void draw(Image& img);

};

#endif
