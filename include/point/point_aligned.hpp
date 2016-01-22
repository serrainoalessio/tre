#ifndef POINT_ALIGNED_HPP
#define POINT_ALIGNED_HPP

#include "point/point.hpp"
#include "geometry_approx.hpp"

template <typename float_type, int dim>
bool aligned(const point<float_type, dim>& op1, const point<float_type, dim>& op2, const point<float_type, dim>& op3)
{
    float_type lratio, id_ratio, tmp, tmp2;
    if (op1 == op2 || op1 == op3 || op2 == op3)
        return false; // it might be true or false
    lratio = euclidean_distance(op1, op2)/euclidean_distance(op1, op3);
    for (size_t i = 0; i < dim; i++) {
        tmp = diffid(op1, op3, i);
        tmp2 =  diffid(op1, op2, i);
        if (tmp == (float_type)0.0) {
            if (tmp2 == (float_type)0.0)
                continue; // good data up to now
            else
                return false;
        }
        id_ratio = tmp2/tmp;
        if (valcmp_nequals(id_ratio, lratio))
            return false;
    }
    return true;
}

#endif // POINT_ALIGNED_HPP defined
