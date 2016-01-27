#include "graphics/graphics.hpp"

namespace GUI{

    //constexpr Color RED(255,0,0); 

    Color::Color(Uint8 _r,Uint8 _g,Uint8 _b,Uint8 _a):r(_r),g(_g),b(_b),a(_a){

    }

    void Color::set(SDL_Renderer* renderer){
        SDL_SetRenderDrawColor(renderer,r,g,b,a);
    }

}
