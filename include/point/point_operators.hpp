#ifndef POINT_OPERATORS_HPP
#define POINT_OPERATORS_HPP

#include "point.hpp"
#include "../geometry_approx.hpp"
#include <algorithm>
#include <functional>

template <class operation, typename float_type, int dim> point<float_type, dim>
    plus_minus_helper(const point<float_type, dim>& op1, const point<float_type, dim>& op2);

template <bool approx, typename float_type, int dim>
    bool operator==(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{ /*** TWO POINTS ARE EQUAL IF AND ONLY IF ALL THEIR COORDINATES ARE EQUAL ***/
    static_assert(std::is_same<decltype(op1.coords), std::array<float_type, dim>>::value,
                  "You must use an array type to store point coordinates");
    auto op1begin = op1.coords.begin(), op2begin = op2.coords.begin();
    if (approx) {
        return std::all_of(op1.coords.begin(),
                           op1.coords.end(),
                           [op1begin, op2begin](const float_type& i) -> bool { return valcmp_equals(i, *(op2begin + (&i - op1begin))); });
    } else {
        return std::all_of(op1.coords.begin(),
                           op1.coords.end(),
                           [op1begin, op2begin](const float_type& i) -> bool { return i == *(op2begin + (&i - op1begin)); });
    }
}

template <bool approx, typename float_type, int dim>
    bool operator!=(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{
    static_assert(std::is_same<decltype(op1.coords), std::array<float_type, dim>>::value,
                  "You must use an array type to store point coordinates");
    auto op1begin = op1.coords.begin(), op2begin = op2.coords.begin();
    if (approx) {
        return std::any_of(op1.coords.begin(),
                           op1.coords.end(),
                           [op1begin, op2begin](const float_type& i) -> bool { return valcmp_nequals(i, *(op2begin + (&i - op1begin))); });
    } else {
        return std::any_of(op1.coords.begin(),
                           op1.coords.end(),
                           [op1begin, op2begin](const float_type& i) -> bool { return i != *(op2begin + (&i - op1begin)); });
    }
}

template <typename float_type, int dim>
    point<float_type, dim> operator+(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{
    return plus_minus_helper<std::plus<float_type>>(op1, op2);
}

template <typename float_type, int dim>
    point<float_type, dim> operator-(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{
    return plus_minus_helper<std::minus<float_type>>(op1, op2);
}


template <class operation, typename float_type, int dim> point<float_type, dim>
    plus_minus_helper(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{
    static_assert(std::is_same<decltype(op1.coords), std::array<float_type, dim>>::value,
                  "You must use an array type to store point coordinates");
    
    point<float_type, dim> result;
    std::transform(op1.coords.begin(), op1.coords.end(), op2.coords.begin(), result.coords.begin(), operation());
    return result;
}

#endif // POINT_OPERATORS_HPP