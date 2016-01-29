#ifndef GUI_POINT_HPP
#define GUI_POINT_HPP

#include <SDL.h>
#include <iostream>
#include <vector>

using namespace std;

#include "color.hpp"
#include "drawing-functions.hpp"


namespace GUI{

    class Point{
    public:
        int x,y;
        Color color;

        int radius;
        bool draggable;

        Point(){};
        Point(int _x,int _y,Color _color,int _radius = 5,bool _draggable = false);
        void draw(SDL_Renderer* renderer);

        bool isInside(int x0,int y0);
    };

    std::ostream& operator << (std::ostream &os, const Point &p);

}

#endif
