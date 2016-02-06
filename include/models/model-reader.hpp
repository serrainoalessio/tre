#ifndef MODEL_READER_HPP
#define MODEL_READER_HPP

#include <fstream>
#include <iostream>
#include "geometry.hpp"

using namespace std;

class ModelReader{
    int intBuffer[100];

    ModelReader(){};

    void read(string path);

};


#endif
