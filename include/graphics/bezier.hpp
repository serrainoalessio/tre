#ifndef GUI_BEZIER_HPP
#define GUI_BEZIER_HPP

#include <SDL.h>
#include <iostream>
#include <vector>
using namespace std;

#include "color.hpp"
#include "point.hpp"

namespace GUI{

    class Bezier{
    public:
        vector<int>list;
        //vector<Point2D> fltPoints;

        Color color;
        int samples;

        int* data = nullptr;

        Bezier(){};
        Bezier(Bezier& b);
        Bezier(GUI::Color _color,int _samples = 50);

        void addPoint(int p);
        void draw(SDL_Renderer* renderer,Point* points);

        ~Bezier();
    };

}

#endif
