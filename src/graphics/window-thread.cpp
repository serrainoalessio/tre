#include "graphics/graphics.hpp"

namespace GUI{

    WindowThread::WindowThread(int w,int h):width(w),height(h){
        points.reserve(100);
    }

    void WindowThread::start(string title){
        window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );

        myThread = thread(&WindowThread::init,this);
    }

    void WindowThread::init(){
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        /*
        setColor(0,0,0);
        drawRect(0,0,width,height);
        */

        //setColor(255,255,255);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        fillCircle(renderer,width/2,height/2,10);

        updateScreen();

        eventLoop();
    }

    void WindowThread::addPoint(const Point& p){
        points.push_back(p);
        pointCount++;
    }

    void WindowThread::eventLoop(){
        SDL_Event event;
        while (true){
            while(SDL_PollEvent(&event) != 0){
                switch(event.type){
                    case SDL_QUIT:
                        cout << "Closed" << endl;
                        closed = true;
                        return;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if(onClick != nullptr){
                            onClick(*this,event.button.x,event.button.y);
                        }
                        break;
                }
            }

            if(drawnCount != pointCount){
                //cout << "Drawing " << pointCount - drawnCount << " points" << endl;
                for(int i = drawnCount;i < pointCount;i++){
                    points[i].draw(renderer);
                }
                drawnCount = pointCount;
                updateScreen();
            }

            if(quit)return;

            SDL_Delay(50);
        }
    }

    void WindowThread::updateScreen(){
        SDL_RenderPresent(renderer);
    }

    void WindowThread::wait(){
        if(myThread.joinable() )myThread.join();
    }

}
