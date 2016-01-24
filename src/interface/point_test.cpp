#include <iostream>
#include "geometry.hpp" // geometry header
#include "misc.hpp"

using namespace std;

int main() {
    Point2D temp;
    Point2DCentroid centroid;

    for(int i = 0;i < 100;i++){
        temp = Point2D(randRange(0.0f, 1.0f), randRange(-1.0f, 1.0f));
        // cout << temp.X() << " " << temp.Y() << endl;
        centroid.add(temp);
    }

    auto center = centroid.get();
    cout << center.X() << " " << center.Y() << endl;

    Point2D A(3, 5), B(1, 7), C;
    float x = 7.0;
    C = A + B; // points are vector
    C -= A;
    C *= x;
    cout << C.X() << " " << C.Y() << endl;

    return 0;
}
