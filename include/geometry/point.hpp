#ifndef POINT_HPP
#define POINT_HPP

#include <stddef.h> // size_t type

#include <array>
#include <utility> // std::pair
#include <algorithm>
#include <initializer_list>

template <typename float_type, int dim = 2>
class point {
private:
    std::array<float_type, dim> coords;
public:
    // operators () and [] gets the coordinates of the point
    const float_type& operator[](size_t id) const; // call on const members
    const float_type& operator()(size_t id) const;
    float_type& operator[](size_t id);
    float_type& operator()(size_t id);
    size_t dimensions(); // returns the number of dimension of the point

    // ===== N.B. For only bi-dimensional points =====
    const float_type& X() const;
    const float_type& Y() const;
    float_type& X();
    float_type& Y();
    // ===== =================================== =====

    // constructors
    point(std::initializer_list<float_type> coordinates);
    point(float_type X = 0, float_type Y = 0);
    point(const point<float_type, dim>& Pt);

    // Comparing operators
    template <bool approx, typename float_type_aux, int dim_aux>
        friend bool operator==(const point<float_type_aux, dim_aux>& op1, const point<float_type_aux, dim_aux>& op2);
    template <bool approx, typename float_type_aux, int dim_aux>
        friend bool operator!=(const point<float_type_aux, dim_aux>& op1, const point<float_type_aux, dim_aux>& op2);
    // it does non exist an order relation between points in more than 1 dimension

    template <class operation_aux, typename float_type_aux, int dim_aux> friend
        point<float_type_aux, dim_aux> plus_minus_helper(const point<float_type_aux, dim_aux>& op1,
                                                         const point<float_type_aux, dim_aux>& op2);
};

/*                                                      *
 * === DISTANCE BETWEEN POINTS ===                      *
 * Minkowsky = general expression for distance          *
 * Euclidean = special case of Minkowsky with n = 2     *
 * ... The others are just implemented ....             *
 *                                                      */
template <typename float_type, int dim>
    float_type minkowsky_distance(const point<float_type, dim>& op1, const point<float_type, dim>& op2, float_type n);
template <typename float_type, int dim>
    float_type euclidean_distance(const point<float_type, dim>& op1, const point<float_type, dim>& op2);
template <typename float_type, int dim>
    float_type manhattan_distance(const point<float_type, dim>& op1, const point<float_type, dim>& op2);
template <typename float_type, int dim>
    float_type chebyshev_distance(const point<float_type, dim>& op1, const point<float_type, dim>& op2);

/* === SPECIAL PURPOSE DISTANCE === */
template <typename float_type, int dim> /* returns minkowsky_distance raised to the n-th power */
    float_type minkowsky_distancen(const point<float_type, dim>& op1, const point<float_type, dim>& op2,  float_type n);
template <typename float_type, int dim> /* returns the square of euclidean distance */
    float_type euclidean_distance2(const point<float_type, dim>& op1, const point<float_type, dim>& op2);

/* === DIFFERENCE OF COORDINATES === */
template <typename float_type, int dim>
    float_type diffid(const point<float_type, dim>& op1, const point<float_type, dim>& op2, size_t n);

/* === INTENDED TO BE USED IF HAVE AT LEAST TWO DIMENSIONS === */
template <typename float_type, int dim>
    float_type diffx(const point<float_type, dim>& op1, const point<float_type, dim>& op2);
template <typename float_type, int dim>
    float_type diffy(const point<float_type, dim>& op1,const point<float_type, dim>& op2);


template <bool approx = true, typename float_type, int dim>
    bool operator==(const point<float_type, dim>& op1, const point<float_type, dim>& op2);
template <bool approx = true, typename float_type, int dim>
    bool operator!=(const point<float_type, dim>& op1, const point<float_type, dim>& op2);
// it does non exist an order relation between points in more than 1 dimension

/* === THIS MAY BE USEFUL WHEN TREATING POINTS AS VECTORS === */
template <typename float_type, int dim>
    point<float_type, dim> operator-(const point<float_type, dim>& op1, const point<float_type, dim>& op2);
template <typename float_type, int dim>
    point<float_type, dim> operator+(const point<float_type, dim>& op1, const point<float_type, dim>& op2);
template <typename float_type, int dim>
    point<float_type, dim> operator*(point<float_type, dim> const& op1, float_type& op2);
template <typename float_type, int dim>
    point<float_type, dim> operator/(point<float_type, dim> const& op1, float_type& op2);

/* === UTILITIES === */
template <typename float_type, int dim>
    bool aligned(const point<float_type, dim>& op1, const point<float_type, dim>& op2, const point<float_type, dim>& op3);
template <typename float_type, int dim>
    bool aligned(std::initializer_list< const point<float_type, dim> > pts);

#endif // POINT_HPP defined
