/* Instantiation of the point method */
#include "geometry/point.hpp"


// include all function definitions
#include "geometry/point/point_operators.hpp"
#include "geometry/point/point_distance.hpp"
#include "geometry/point/point_aligned.hpp"

template class point<float, 2>; // explicit template instantiation

// instantiation of all the functions
template point<float, 2> operator-(point<float, 2> const& op1, point<float, 2> const& op2);
template point<float, 2> operator+(point<float, 2> const& op1, point<float, 2> const& op2);
template point<float, 2> operator*(point<float, 2> const& op1, float& op2);
template point<float, 2> operator/(point<float, 2> const& op1, float& op2);

// VERY IMPORTANT TODO: instantiate all other functions
