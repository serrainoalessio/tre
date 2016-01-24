#include "geometry/point.hpp"
#include "geometry/centroid.hpp"
#include "geometry_approx.hpp"
#include <algorithm> // std::for_each

template <typename float_type, int dim>
    point_centroid<float_type, dim>::point_centroid() : total_weight(0) {
        for (size_t i = 0; i < dim; i++) sum(i) = 0; // sets to zero each component
    }

template <typename float_type, int dim>
    point_centroid<float_type, dim>& point_centroid<float_type, dim>::add(point<float_type, dim> pt, float weight) {
        sum += (pt * weight);
        total_weight += weight;
        return *this;
    }

template <typename float_type, int dim>
    point<float_type, dim> point_centroid<float_type, dim>::get() {
        point<float_type, dim> ret; // trust in RVO!
        ret = sum / total_weight;
        return ret;
    }


template <typename float_type, int dim>
    point<float_type, dim> centroid(std::initializer_list< const point<float_type, dim> > pts) {
        // TODO: this funcition
    }

template <typename float_type, int dim>
    point<float_type, dim> centroid_weight(std::initializer_list< std::pair< const point<float_type, dim>, int > >) {
        // TODO: this function
    }
