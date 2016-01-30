#include "graphics/window.hpp"

bool SDL_INITIALIZED = false;

namespace GUI{

    /***********************************
    --------   WINDOW THREAD  ----------
    ***********************************/

    WindowThread::WindowThread(int w,int h):width(w),height(h),points(100),rects(50),beziers(20){
    }

    void WindowThread::start(string title){
        window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );

        myThread = thread(&WindowThread::init,this);
    }

    void WindowThread::init(){
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        reset();

        eventLoop();
    }

    void WindowThread::addPoint(const Point& p){
        points.push_back(p);
    }

    void WindowThread::eventLoop(){
        SDL_Event event;
        while (true){
            lock.lock();
            while(SDL_PollEvent(&event) != 0){
                switch(event.type){
                    case SDL_QUIT:
                        cout << "Closed" << endl;
                        closed = true;
                        return;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        //if not clicking on a draggable point and if there is one call the callback
                        if(!clickOnPoint(event.button.x,event.button.y) && onClick != nullptr){
                            onClick(*this,event.button.x,event.button.y);
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        currentDragging = -1;
                        break;
                    case SDL_MOUSEMOTION:
                        if(currentDragging > -1){
                            points[currentDragging].x += event.motion.xrel;
                            points[currentDragging].y += event.motion.yrel;
                            redraw();
                        }
                        break;
                    case SDL_KEYDOWN:
                        switch( (char)event.key.keysym.sym ){
                            case 's':
                                cout << "Saving" << endl;
                                break;
                        }
                        break;
                }
            }

            bool needRedraw = false;

            if(background != nullptr){
                if(background_tex != nullptr){
                    SDL_DestroyTexture(background_tex);
                }

                background_tex = SDL_CreateTextureFromSurface(renderer,background);
                SDL_FreeSurface(background);
                background = nullptr;
                SDL_RenderCopy(renderer,background_tex,nullptr,nullptr);
                needRedraw = true;
            }

            //draw only new items and update the screen if needed
            if( drawRects() )needRedraw = true;
            if( drawBeziers() )needRedraw = true;
            if( drawPoints() )needRedraw = true;

            if(needRedraw){
                updateScreen();
            }

            if(points.empty() && drawnPoints != 0){
                reset();
            }

            if(quit)return;
            lock.unlock();

            SDL_Delay(10);
        }
    }

    void WindowThread::drawBackground(){
        if(background_tex != nullptr){
            SDL_RenderCopy(renderer,background_tex,nullptr,nullptr);
        }
    }

    bool WindowThread::drawBeziers(){
        if(drawnBeziers < beziers.size()){
            for(int i = drawnBeziers;i < beziers.size();i++){
                beziers[i].draw(renderer,&points[0]);
            }
            drawnBeziers = beziers.size();
            return true;
        }else{
            return false;
        }
    }

    bool WindowThread::drawRects(){
        if(drawnRects < rects.size()){
            for(int i = drawnRects;i < rects.size();i++){
                rects[i].draw(renderer,&points[0]);
            }
            drawnRects = rects.size();
            return true;
        }else{
            return false;
        }
    }

    bool WindowThread::drawPoints(){
        if(drawnPoints < points.size()){
            for(int i = drawnPoints;i < points.size();i++){
                points[i].draw(renderer);
            }
            drawnPoints = points.size();
            return true;
        }else{
            return false;
        }
    }

    void WindowThread::redraw(){
        reset(false);
        drawnPoints = 0;
        drawnRects = 0;
        drawnBeziers = 0;

        drawBackground();
        drawRects();
        drawBeziers();
        drawPoints();

        updateScreen();
    }

    void WindowThread::reset(bool show){
         SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
         SDL_RenderClear(renderer);

         if(show)updateScreen();
    }

    void WindowThread::updateScreen(){
        SDL_RenderPresent(renderer);
    }

    void WindowThread::wait(){
        if(myThread.joinable() )myThread.join();
    }

    bool WindowThread::clickOnPoint(int x,int y){
        currentDragging = -1;
        for(int i = 0;i < points.size();i++){
            if(points[i].isInside(x,y)){
                if(points[i].draggable)currentDragging = i;
                return true;
            }
        }
        return false;
    }


    /***********************************
    ------------  WINDOW  --------------
    ***********************************/


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

    void Window::setBackground(unsigned char* pixels){
        lock();
        win.background = SDL_CreateRGBSurfaceFrom((void*)pixels,
            win.width,
            win.height,
            24,
            win.width*3,
            0xff0000, 0x00ff00, 0x0000ff, 0
        );
        unlock();
    }
}
