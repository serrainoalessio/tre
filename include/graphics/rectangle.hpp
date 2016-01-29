#ifndef GUI_RECTANGLE_HPP
#define GUI_RECTANGLE_HPP

#include <SDL.h>
#include <iostream>
#include <vector>

using namespace std;

#include "point.hpp"
#include "color.hpp"


namespace GUI{

    class Rectangle{
    public:
        int a,b;
        Color color;
        SDL_Rect rect;

        Rectangle(){};
        Rectangle(int _a,int _b,GUI::Color _color);

        void draw(SDL_Renderer* renderer,Point* points);
    };

}

#endif
