#ifndef POINT_DISTANCE_HPP
#define POINT_DISTANCE_HPP

#include "geometry/point.hpp"
#include "geometry_approx.hpp"

#include <cmath> // sqrt, pow, abs

template <typename float_type, int dim>
    float_type minkowsky_distancen(const point<float_type, dim>& op1,
                                   const point<float_type, dim>& op2,  float_type n)
{
    float_type temp, sum = 0;
    for (size_t i = 0; i < dim; i++) {
        temp = diffid(op1, op2, i);
        std::abs(temp, temp);
        std::pow(temp, temp, n);
        sum += temp;
    }
    return sum;
}

template <typename float_type, int dim>
    float_type minkowsky_distance(const point<float_type, dim>& op1,
                                  const point<float_type, dim>& op2,  float_type n)
{
    float_type value = minkowsky_distancen(op1, op2, n);
    std::pow(value, value, 1.0/n);
    return value;
}

// Now, other cases of distance are special case
// n = 1    Manhattan Distance
// n = 2    Euclidean Distance
// n = +inf Chebyshev Distance
template <typename float_type, int dim>
    float_type euclidean_distance(const point<float_type, dim>& op1,
                                  const point<float_type, dim>& op2)
{ /* === Returns the distance === */
    return minkowsky_distance(op1, op2, 2.0); // particular case
}

template <typename float_type, int dim>
    float_type euclidean_distance2(const point<float_type, dim>& op1,
                                   const point<float_type, dim>& op2)
{ /* === Returns the square of distance === */
    return minkowsky_distancen(op1, op2, 2.0); // particular case
}

template <typename float_type, int dim>
    float_type chebyshev_distance(const point<float_type, dim>& op1,
                                  const point<float_type, dim>& op2 )
{
    // Obviusly I cannot call minkowsky_distance with n = inf
    // this case simply return the max difference
    float_type temp, best = 0;
    for (size_t i = 0; i < dim; i++) {
        temp = diffid(op1, op2, i);
        std::abs(temp, temp);
        best = (temp > best)?temp:best; // set best to the maximum
    }
    return best; // returns the maximum
}


template <typename float_type, int dim>
    float_type diffid(const point<float_type, dim>& op1, const point<float_type, dim>& op2, size_t n)
{ // single coordinate (signed) difference
    return op2(n) - op1(n);
}

/*** SPECIFIC FUNCTIONS ****/
template <typename float_type, int dim> float_type
    diffx(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{
    return op2.X() - op1.X();
}
template <typename float_type, int dim>
    float_type diffy(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{
    return op2.Y() - op1.Y();
}

#endif // POINT_DISTANCE_HPP defined
