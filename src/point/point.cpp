/* Instantiation of the point method */
#include "geometry/point.hpp"

// include all function definitions
#include "geometry/point/point_operators.hpp"
#include "geometry/point/point_distance.hpp"
#include "geometry/point/point_aligned.hpp"

template<> class point<float, 2>; // explicit template instantiation
