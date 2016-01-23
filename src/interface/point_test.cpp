
#include <iostream>
#include "geometry.hpp" // geometry header
#include "misc.hpp"

using namespace std;

int main() {

   Point2DCentroid centroid;

   for(int i = 0;i < 100;i++){
      centroid.add(Point2D(randRange(-1.0f,1.0f),randRange(-1.0f,1.0f)));
   }

   auto center = centroid.get();
   cout << center[0] << " " << center[1] << endl;
    /*
    point2d_t A(3, 5), B(1, 7), C;
    C = A + B; // points are vector
    cout << C.X() << " " << C.Y() << endl;
    */
    return 0;
}
