#include "image/transform.hpp"

void ImageTransform::setRotation(float angle){
    transform(0,0) = cos(angle);
    transform(1,0) = -sin(angle);
    transform(0,1) = sin(angle);
    transform(1,1) = cos(angle);
}

ImageTransform::ImageTransform(Point2D _center,Point2D _translation,float angle):center(_center),scaledCenter(_center),translation(_translation),transform(2,2){

    setRotation(angle);
}

void ImageTransform::scale(float sx,float sy){
    if(sy == 0)sy = sx;

    transform(0,0) *= sx;
    transform(1,0) *= sy;
    transform(0,1) *= sx;
    transform(1,1) *= sy;


    translation[0] *= sx;
    translation[1] *= sy;
    scaledCenter[0] *= sx;
    scaledCenter[1] *= sy;
}

void ImageTransform::apply(Point2D& point){
    float x = point[0] - center[0];
    float y = point[1] - center[1];

    point[0] = x*transform(0,0) + y*transform(1,0) + translation[0] + scaledCenter[0];
    point[1] = x*transform(0,1) + y*transform(1,1) + translation[1] + scaledCenter[1];
}

void ImageTransform::apply(vector<Point2D>& points){
    for (size_t i = 0; i < points.size(); i++) {
        apply(points[i]);
    }
}
