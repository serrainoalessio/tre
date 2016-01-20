#include "point.hpp"
#include <iostream>
using namespace std;

int main() {
    Point<2> A(3, 5), B(1, 7), C;
    C = A + B; // points are vector
    cout << C << endl;
    return 0;
}
