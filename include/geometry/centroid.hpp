#ifndef CENTROID_HPP
#define CENTROID_HPP

#include <initializer_list>
#include <utility> // std::pair
#include "geometry/point.hpp"

template <typename float_type, int dim = 2>
class point_centroid {
    point<float_type, dim> sum; // sum of all POINTS
    float total_weight;
public:
    point_centroid();

    point_centroid& add(point<float_type, dim>, float weight = 1);
    point<float_type, dim> get();
};

template <typename float_type, int dim>
    point<float_type, dim> centroid(std::initializer_list< const point<float_type, dim> > pts);
template <typename float_type, int dim>
    point<float_type, dim> centroid_weight(std::initializer_list< std::pair< const point<float_type, dim>, int > >);

#endif // CENTROID_HPP defined
