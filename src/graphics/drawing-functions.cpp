#include "graphics/graphics.hpp"

namespace GUI{

    void fillCircle(SDL_Renderer* renderer,int x0, int y0, int r){
        int x = r;
        int y = 0;
        int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

        while( y <= x ){
            //setPixel( x + x0,  y + y0); // Octant 1
            //setPixel(-x + x0,  y + y0); // Octant 4
            SDL_RenderDrawLine(renderer,x + x0,  y + y0,-x + x0,  y + y0 );

            //setPixel( y + x0,  x + y0); // Octant 2
            //setPixel(-y + x0,  x + y0); // Octant 3
            SDL_RenderDrawLine(renderer,y + x0,  x + y0,-y + x0,  x + y0 );

            //setPixel(-x + x0, -y + y0); // Octant 5
            //setPixel( x + x0, -y + y0); // Octant 7
            SDL_RenderDrawLine(renderer,-x + x0, -y + y0,x + x0, -y + y0 );

            //setPixel(-y + x0, -x + y0); // Octant 6
            //setPixel( y + x0, -x + y0); // Octant 8
            SDL_RenderDrawLine(renderer,-y + x0, -x + y0, y + x0, -x + y0);

            y++;
            if(decisionOver2<=0){
                decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
            } else {
                x--;
                decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
            }
        }
    }

}
