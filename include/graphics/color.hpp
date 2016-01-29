#ifndef GUI_COLOR_HPP
#define GUI_COLOR_HPP

#include <SDL.h>
#include <iostream>
#include <vector>

using namespace std;

namespace GUI{

    class Color{
    public:
        Uint8 r,g,b,a;

        Color(){};
        Color(Uint8 _r,Uint8 _g,Uint8 _b,Uint8 _a = 255);
        void set(SDL_Renderer* renderer);
    };

}

#endif
