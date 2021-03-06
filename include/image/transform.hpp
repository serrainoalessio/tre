#ifndef IMAGE_TRANSFORM_HPP
#define IMAGE_TRANSFORM_HPP

#include "geometry.hpp"
#include "image.hpp"


#include <vector>

using namespace std;

class ImageTransform{
    void setRotation(float angle);

public:
    Point2D translation;
    Image transform;

    ImageTransform(){};
    ImageTransform(Point2D _center,float angle);

    void scale(float sx,float sy = 0);

    void apply(Point2D& point) const;
    void apply(vector<Point2D>& points) const;

};


#endif
