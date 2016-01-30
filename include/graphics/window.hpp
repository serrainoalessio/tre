#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include <SDL.h>
#include <iostream>
#include <vector>

#include <thread>
#include <atomic>
#include <mutex>

using namespace std;

#include "point.hpp"
#include "color.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "bezier.hpp"
#include "lock-free-vector.hpp"


namespace GUI{

    class WindowThread{
        friend class Window;

        SDL_Window* window;
        SDL_Renderer* renderer;

        SDL_Surface* background = nullptr;
        SDL_Texture* background_tex = nullptr;

        thread myThread;
        mutex lock;

        int drawnPoints = 0;
        int drawnRects = 0;
        int drawnBeziers = 0;


        void init();
        void eventLoop();

        void drawBackground();
        bool drawRects();
        bool drawPoints();
        bool drawBeziers();


        void updateScreen();
        void redraw();

        int currentDragging = -1;
        bool clickOnPoint(int x,int y);

    protected:
        //callbacks
        void (*onClick)(WindowThread& win,int x,int y) = nullptr;

    public:
        const int width,height;

        atomic<bool> closed {false};
        atomic<bool> quit {false};

        LockFreeVector<GUI::Point> points;
        LockFreeVector<GUI::Rectangle> rects;
        LockFreeVector<GUI::Bezier> beziers;


        WindowThread(int w = 640,int h = 480);

        void start(string title);
        void addPoint(const Point& p);

        void reset(bool show = true);

        void wait();
    };


    class Window{
        void initialize_SDL();

    public:

        WindowThread win;

        Window(string title,int w = 640,int h = 480);

        void wait();

        void onClick(void (*f)(WindowThread& win,int x,int y));
        void reset();

        int addPoint(Point p);
        int addRectangle(Point a,Point b,Color color);
        int addBezier(Bezier& bez);

        void lock();
        void unlock();

        void setBackground(unsigned char* pixels);
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
