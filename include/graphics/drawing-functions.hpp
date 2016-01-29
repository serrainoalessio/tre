#ifndef GUI_DRAWING_FUNCTIONS_HPP
#define GUI_DRAWING_FUNCTIONS_HPP

#include <SDL.h>

using namespace std;


namespace GUI{

    void fillCircle(SDL_Renderer* renderer,int x,int y,int r);
    void strokeCircle(SDL_Renderer* renderer,int x,int y,int r);

}

#endif
