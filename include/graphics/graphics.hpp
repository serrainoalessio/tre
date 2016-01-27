#ifndef GRAPHICS_H
#define GRAPHICS_H

//Using SDL and standard IO
#include <SDL.h>
#include <iostream>
#include <vector>

#include <thread>
#include <atomic>


#include "misc.hpp"


using namespace std;


namespace GUI{

    void fillCircle(SDL_Renderer* renderer,int x,int y,int r);

    class Color{
    public:
        Uint8 r,g,b,a;

        Color(){};
        Color(Uint8 _r,Uint8 _g,Uint8 _b,Uint8 _a = 255);
        void set(SDL_Renderer* renderer);
    };

    class Point{
    public:
        int x,y;
        Color color;

        int radius;
        bool draggable;

        Point(){};
        Point(int _x,int _y,Color _color,int _radius = 5,bool _draggable = false);
        void draw(SDL_Renderer* renderer);
    };

    class WindowThread{
        friend class Window;

        SDL_Window* window;
        SDL_Renderer* renderer;

        thread myThread;

        int drawnCount = 0;


        void init();
        void eventLoop();
        void updateScreen();

    protected:
        //callbacks
        void (*onClick)(WindowThread& win,int x,int y) = nullptr;

    public:
        const int width,height;

        atomic<bool> closed {false};
        atomic<bool> quit {false};
        atomic<int> pointCount {0};

        vector<GUI::Point> points;


        WindowThread(int w = 640,int h = 480);

        void start(string title);
        void addPoint(const Point& p);

        void wait();
    };


    class Window{


        void initialize_SDL();

    public:

        WindowThread win;

        Window(string title,int w = 640,int h = 480);

        void wait();

        void onClick(void (*f)(WindowThread& win,int x,int y));

        /*
        Window(string title,int w = 640,int h = 480):win(w,h){
            if(!SDL_INITIALIZED){
                initialize_SDL();
            }

            win.start(title);



            needUpdate = true;

        }

        void setColor(Uint8 r = 0,Uint8 g = 0,Uint8 b = 0,Uint8 alpha = 255){
            SDL_SetRenderDrawColor(renderer,r,g,b,alpha);
        }

        void drawRect(int x,int y,int w,int h){
            SDL_Rect rectangle;
            rectangle.x = x;
            rectangle.y = y;
            rectangle.w = w;
            rectangle.h = h;
            SDL_RenderFillRect(renderer, &rectangle);
        }

        void drawLine(int x1,int y1,int x2,int y2){
            SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
        }

        void setPixel(int x,int y){
            SDL_RenderDrawPoint(renderer,x,y);
        }



        void wait(){
            if(eventThread.joinable() )eventThread.join();
        }

        void close(){
            quit = true;
            this->wait();
        }


        ~Window(){
            SDL_DestroyWindow( window );
            this->wait();
            SDL_Quit();
        }
        */

    };

}

#endif
