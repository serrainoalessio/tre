#include "graphics.hpp"
#include "image/image.hpp"
#include "image/transform.hpp"
#include "dataset/dataset.hpp"

#include "misc.hpp"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


void click(GUI::WindowThread& win,int x,int y){
    GUI::Color color(255,0,0);
    GUI::Point point(x,y,color,5,true);

    cout << "New point " << point << endl;

    win.addPoint(point);
}

int main(){
    //define some colors
    const GUI::Color red(255,0,0);
    const GUI::Color green(0,255,0);
    const GUI::Color blue(0,0,255);
    const GUI::Color white(255,255,255);

    int displayScale = 10;

    //read the image
    Image test(imread("data/test.png",0));

    //compute centroid and direction
    Point2D center = test.centroid();
    float dir = test.direction(center);

    //compute the transformation
    ImageTransform transformation(center,dir);
    transformation.scale(displayScale);

    //create the window
    GUI::Window win("test",test.cols * displayScale,test.rows * displayScale);

    //convert and upscale the image and add it to the window
    Mat drawing = test.toColorMat(displayScale);
    win.setBackground(drawing.data);

    //wait for the window to close
    win.wait();

    return 0;
    /*
    //add a new point when clicking on an empty area
    //win.onClick(click);

    GUI::Bezier curve1(white);
    GUI::Bezier curve2(white);

    int a = win.addPoint(GUI::Point(200,200,green,10,true));
    int b = win.addPoint(GUI::Point(250,150,red,10,true));
    int c = win.addPoint(GUI::Point(150,150,red,10,true));
    int d = win.addPoint(GUI::Point(250,250,blue,10,true));
    int e = win.addPoint(GUI::Point(250,150,blue,10,true));

    curve1.addPoint(a);
    curve1.addPoint(b);
    curve1.addPoint(c);
    curve1.addPoint(a);

    curve2.addPoint(a);
    curve2.addPoint(d);
    curve2.addPoint(e);
    curve2.addPoint(a);


    win.addBezier(curve1);
    win.addBezier(curve2);

    //create a rectangle using this 2 points
    //win.addRectangle(a,b,blue);

    return 0;
    */
}
