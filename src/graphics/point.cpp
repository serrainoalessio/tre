#include "graphics/graphics.hpp"

namespace GUI{

    Point::Point(int _x,int _y,Color _color,int _radius,bool _draggable):x(_x),y(_y),color(_color),radius(_radius),draggable(_draggable){

    }

    void Point::draw(SDL_Renderer* renderer){
        color.set(renderer);
        fillCircle(renderer,x,y,radius);
    }

}
