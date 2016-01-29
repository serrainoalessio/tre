#include "graphics/point.hpp"
#include "graphics/color.hpp"

namespace GUI{

    Point::Point(int _x,int _y,Color _color,int _radius,bool _draggable):x(_x),y(_y),color(_color),radius(_radius),draggable(_draggable){

    }

    void Point::draw(SDL_Renderer* renderer){
        color.set(renderer);
        fillCircle(renderer,x,y,radius);
    }

    bool Point::isInside(int x0,int y0){
        return (x-x0)*(x-x0) + (y-y0)*(y-y0) <= radius*radius;
    }

    std::ostream& operator << (std::ostream &os, const Point &p){
        os << "(" << p.x << " , " << p.y << ")";
        return os;
    }
}
