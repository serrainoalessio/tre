#include "graphics/graphics.hpp"

bool SDL_INITIALIZED = false;

namespace GUI{

    void Window::initialize_SDL(){
        if(SDL_Init(SDL_INIT_VIDEO) < 0){
            cerr << CONSOLE_RED << "Error initializing SDL " << SDL_GetError() << CONSOLE_RESET << endl;
            throw 0;
        }
    }

    Window::Window(string title,int w,int h):win(w,h){
        if(!SDL_INITIALIZED){
            initialize_SDL();
        }

        win.start(title);
    }

    void Window::wait(){
        win.wait();
    }

    void Window::onClick(void (*f)(WindowThread& win,int x,int y)){
        win.onClick = f;
    }

    int Window::addPoint(Point p){
        win.points.push_back(p);
        return win.points.size() - 1;
    }

    int Window::addRectangle(Point a,Point b,Color color){
        int A = addPoint(a);
        int B = addPoint(b);

        win.rects.push_back(Rectangle(A,B,color));
        return win.rects.size() - 1;
    }

    int Window::addBezier(Bezier& bez){
        win.beziers.push_back(bez);
        return win.beziers.size() - 1;
    }

    void Window::lock(){
        win.lock.lock();
    }

    void Window::unlock(){
        win.lock.unlock();
    }

    void Window::reset(){
        win.points.clear();
        win.rects.clear();
    }
}
