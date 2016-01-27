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
}
