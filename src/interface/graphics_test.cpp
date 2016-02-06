#include "graphics.hpp"
#include "image/image.hpp"
#include "image/transform.hpp"
#include "dataset/dataset.hpp"
#include "geometry.hpp"


#include "misc.hpp"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <fstream>

using namespace cv;
using namespace std;


void click(GUI::WindowThread& win,int x,int y){
    GUI::Color color(255,0,0);
    GUI::Point point(x,y,color,5,true);

    cout << "New point " << point << endl;

    win.addPoint(point);
}

Point2D getSize(std::vector<Point2D>& points){
    float x = points[0][0];
    float y = points[0][1];
    float X = points[0][0];
    float Y = points[0][1];

    for (size_t i = 1; i < points.size(); i++) {
        if(x < points[i][0])x = points[i][0];
        if(y < points[i][1])y = points[i][1];
        if(X > points[i][0])X = points[i][0];
        if(Y > points[i][1])Y = points[i][1];
    }

    return Point2D(X-x, Y-y);
}

void keyPress(GUI::WindowThread& win,char k){
    if(k == 's'){
        cout << "Save model to file, enter filename: " << endl;
        string name;
        cin >> name;
        string path = "models/" + name;

        ofstream file;
        file.open(path);

        cout << "Saving to " << path <<" ...    ";

        win.writeToFile(file);

        cout << "OK" << endl;

        file.close();
    }
}

int main(){

    //define some colors
    const GUI::Color red(255,0,0);
    const GUI::Color green(0,255,0);
    const GUI::Color blue(0,0,255);
    const GUI::Color white(255,255,255);

/*
    int displayScale = 10;

    //read the image
    Image test(imread("data/test.png",0));

    //compute centroid and direction
    Point2D centroid = test.centroid();
    float dir = test.direction(centroid);


    vector<Point2D>points;
    test.highPass(0.3);
    test.extractPoints(points);


    //compute the transformation
    Point2D center = Point2D(test.cols/2.0f,test.rows/2.0f);
    ImageTransform transformation(center,center - centroid,dir);
    transformation.scale(displayScale);
    transformation.apply(points);

    Point2D imgScale = getSize(points);

    cout << imgScale[0] << " " <<  imgScale[1] << endl;

    vector<Point2D>modelPoints;
    modelPoints.push_back(Point2D(0,-1));
    modelPoints.push_back(Point2D(-0.2,-0.5));
    modelPoints.push_back(Point2D(0.2, 0.5));
    modelPoints.push_back(Point2D(0, 1));

    ImageTransform modelT(Point2D(0,0),Point2D(0,0),0);
    modelT.scale(imgScale[0]/0.4,imgScale[1]/2.0);
    modelT.scaledCenter = Point2D(140,140);
    modelT.apply(modelPoints);


    //create the window
    GUI::Window win("test",test.cols * displayScale,test.rows * displayScale);




    GUI::Bezier model(white);

    for (size_t i = 0; i < modelPoints.size(); i++) {
        float x = modelPoints[i][0];
        float y = modelPoints[i][1];
        int p = win.addPoint(GUI::Point(x,y,green,10,true));
        model.addPoint(p);
    }

    win.addBezier(model);



    for(size_t i = 0; i < points.size(); i++){
        win.addPoint(GUI::Point(points[i][0],points[i][1],red,3));
    }

    //wait for the window to close
    win.wait();

    return 0;
*/
    //add a new point when clicking on an empty area
    //win.onClick(click);

    GUI::Window win("test",500,500);

    win.onKey(keyPress);

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

    //wait for the window to close
    win.wait();

    //create a rectangle using this 2 points
    //win.addRectangle(a,b,blue);

    return 0;
}
