#include "graphics/graphics.hpp"

void click(GUI::WindowThread& win,int x,int y){
    cout << "Click on " << x << " " << y << endl;

    GUI::Color color(255,0,0);
    GUI::Point point(x,y,color);

    win.addPoint(point);
}

int main(){
    //create a window
    GUI::Window win("test");
    //set a callback on click
    win.onClick(click);

    //use a blocking code to demonstrate multithreading
    int a;
    cin >> a;
    cout << "a = " << a << endl;

    //wait for the window to close
    win.wait();
    return 0;
}
