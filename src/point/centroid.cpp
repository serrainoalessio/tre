#include "geometry/centroid.hpp"
#include "geometry/point/point_centroid.hpp"

template class point_centroid<float, 2>; // explicit template instantiation

template point<float, 2> centroid(std::initializer_list< const point<float, 2> > pts);
template point<float, 2> centroid_weight(std::initializer_list< std::pair< const point<float, 2>, int > > pts);
