#include "graphics/graphics.hpp"

namespace GUI{

    Rectangle::Rectangle(int _a,int _b,Color _color):a(_a),b(_b),color(_color){

    }

    void Rectangle::draw(SDL_Renderer* renderer,Point* points){
        color.set(renderer);

        rect.x = min(points[a].x,points[b].x);
        rect.y = min(points[a].y,points[b].y);
        rect.w = max(points[a].x,points[b].x) - rect.x;
        rect.h = max(points[a].y,points[b].y) - rect.y;

        SDL_RenderFillRect(renderer,&rect);
    }

}
