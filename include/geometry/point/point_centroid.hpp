#include "geometry/point.hpp"
#include "geometry/centroid.hpp"
#include "geometry_approx.hpp"

#include <algorithm> // std::for_each

template <typename float_type, int dim>
    point_centroid<float_type, dim>::point_centroid() : total_weight(0) {
        for (size_t i = 0; i < dim; i++) sum(i) = 0; // sets to zero each component
    }

template <typename float_type, int dim>
    point_centroid<float_type, dim>& point_centroid<float_type, dim>::add(const point<float_type, dim>& pt, float weight) {
        sum += (pt * weight);
        total_weight += weight;
        return *this;
    }

template <typename float_type, int dim>
    point<float_type, dim> point_centroid<float_type, dim>::get() {
        point<float_type, dim> ret; // trust in RVO!

        if (total_weight != 0) // with or without approximation?
            ret = sum / total_weight;
        else // throw an error
            throw ret;

        // now resets each component
        for (size_t i = 0; i < dim; i++) sum(i) = 0; // sets to zero each component
        total_weight = 0;

        return ret;
    }

template <typename float_type, int dim>
    point<float_type, dim> centroid(std::initializer_list< const point<float_type, dim> > pts) {
        point_centroid<float_type, dim> temp; // create a temporany object for calculation
        std::for_each(pts.begin(), pts.end(),
                      [temp]( const point<float_type, dim>& op) mutable -> void {
                          temp.add(op);
                      } );
        return temp.get(); // get the average
    }

template <typename float_type, int dim>
    point<float_type, dim> centroid_weight(std::initializer_list< std::pair< const point<float_type, dim>, int > > pts) {
        point_centroid<float_type, dim> temp; // create a temporany object for calculation
        std::for_each(pts.begin(), pts.end(),
                      [temp](const std::pair<const point<float_type, dim>, int >& op) mutable -> void {
                          temp.add(op.first, op.second);
                        }  );
        return temp.get(); // get the average
    }
