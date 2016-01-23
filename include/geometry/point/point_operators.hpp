#ifndef POINT_OPERATORS_HPP
#define POINT_OPERATORS_HPP

#include "geometry_approx.hpp" // aproximation options
#include "geometry/point.hpp" // base class
#include <algorithm> // std::all_of, std::any_of
#include <functional> // std::plus, std::minus

// operators () and [] gets the coordinates of the point
template <typename float_type, int dim>
    const float_type& point<float_type, dim>::operator[](size_t id) const {
        return coords[id];
    }

template <typename float_type, int dim>
    const float_type& point<float_type, dim>::operator()(size_t id) const {
        return coords[id];
    }

template <typename float_type, int dim>
    float_type& point<float_type, dim>::operator[](size_t id) {
        return coords[id];
    }

template <typename float_type, int dim>
    float_type& point<float_type, dim>::operator()(size_t id) {
        return coords[id];
    }

template <typename float_type, int dim>
    size_t point<float_type, dim>::dimensions() {
        return coords.size(); // should be == dim (template parameter)
    }

// ===== N.B. For only bi-dimensional points =====
template <typename float_type, int dim>
    const float_type& point<float_type, dim>::X() const {
        static_assert(dim >= 1, "Not enough dimensions");
        return this->operator[](0);
    }

template <typename float_type, int dim>
    const float_type& point<float_type, dim>::Y() const {
        static_assert(dim >= 2, "Not enough dimensions");
        return this->operator[](1);
    }

template <typename float_type, int dim>
    float_type& point<float_type, dim>::X() {
        static_assert(dim >= 1, "Not enough dimensions");
        return this->operator[](0);
    }

template <typename float_type, int dim>
    float_type& point<float_type, dim>::Y() {
        static_assert(dim >= 2, "Not enough dimensions");
        return this->operator[](1);
    }
// ===== =================================== =====

// constructors
template <typename float_type, int dim>
    point<float_type, dim>::point(std::initializer_list<float_type> coordinates) {
        std::copy(coordinates.begin(), coordinates.begin() + coords.size(), coords.begin());
    }

template <typename float_type, int dim>
    point<float_type, dim>::point(float_type X, float_type Y): coords({X, Y}) {
        // stops the compilation in case of error
        static_assert(dim == 2, "This option is aviable only for bidimensional points");
    }

template <typename float_type, int dim> // Explicit copy constructor
    point<float_type, dim>::point(const point<float_type, dim>& Pt)
        : coords(Pt.coords)
        { }

template <typename float_type, int dim>
    bool operator==(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{ /*** two points are equal if and only if all theyr coordinates are equals ***/
    static_assert(std::is_same<decltype(op1.coords), std::array<float_type, dim>>::value,
                  "You must use points with the same number of dimension to perform this operation"); // checks data consistence
    return std::mismatch(op1.coords.begin(), op1.coords.end(), op2.coords.begin(),
                        [](const auto it1, const auto it2) -> bool {
                            return eq(*it1, *it2);
                        } ).first() == op1.coords.end();
}

template <typename float_type, int dim>
    bool operator!=(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
{ /*** two points are different if and only if exist at least one coordinate they have different ***/
    static_assert(std::is_same<decltype(op1.coords), std::array<float_type, dim>>::value,
                  "You must use points with the same number of dimension to perform this operation");// checks data consistence
  return std::mismatch(op1.coords.begin(), op1.coords.end(), op2.coords.begin(),
                      [](const auto it1, const auto it2) -> bool {
                          return eq(*it1, *it2);
                      } ).first() != op1.coords.end();
}

template <class operation, typename float_type, int dim> point<float_type, dim>
    plus_minus_helper(const point<float_type, dim>& op1, const point<float_type, dim>& op2);

template <typename float_type, int dim>
    point<float_type, dim> operator+(point<float_type, dim> const& op1, point<float_type, dim> const& op2)
    {
        return plus_minus_helper< std::plus<float_type> >(op1, op2);
    }

template <typename float_type, int dim>
    point<float_type, dim> operator-(point<float_type, dim> const& op1, point<float_type, dim> const& op2)
    {
        return plus_minus_helper< std::minus<float_type> >(op1, op2);
    }

template <class operation, typename float_type, int dim> point<float_type, dim>
    plus_minus_helper(const point<float_type, dim>& op1, const point<float_type, dim>& op2)
    {
        static_assert(std::is_same<decltype(op1.coords), std::array<float_type, dim>>::value,
                      "You must use points with the same number of dimension to perform this operation");

        point<float_type, dim> result;
        std::transform(op1.coords.begin(), op1.coords.end(), op2.coords.begin(), result.coords.begin(), operation());
        return result;
    }

template <typename float_type, int dim>
    point<float_type, dim> operator*(point<float_type, dim> const& op1, float_type& op2)
    {
        point<float_type, dim> result;
        
        return result;
    }
template <typename float_type, int dim>
    point<float_type, dim> operator/(point<float_type, dim> const& op1, float_type& op2)
    {
        point<float_type, dim> result;
        // create correct operation
        return result;
    }

template <class operation, typename float_type, int dim> point<float_type, dim>
    dot_product_helper(point<float_type, dim> const& op1, float_type& op2) {
        point<float_type, dim> result;
        std::transform(op1.coords.begin(), op1.coords.end(), op1.coords.begin(), result.coords.begin(), operation() );
        return result;
    }
#endif // POINT_OPERATORS_HPP
