/*
 *   IMAGE TEST CODE GOES HERE
 */

#include "image/image.hpp"
#include "models/model.hpp"

#include "image/transform.hpp"
#include "dataset/dataset.hpp"

#include "misc.hpp"
#include <fstream>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

float distance(const Point2D& a,const Point2D& b){
	float dx = a[0] - b[0];
	float dy = a[1] - b[1];
	return dx*dx + dy*dy;
}

#define DISPLAY_SCALE  10

inline void draw(Image& test,Image& fitted,Model& model){
	model.draw(fitted);
	imshow("test",test.toColorMat(DISPLAY_SCALE));
	imshow("fitted",fitted.toColorMat(DISPLAY_SCALE));
	waitKey(0);
	fitted.reset();
}

ImageTransform getImageTransform(Image& test){
	//compute centroid and direction
    Point2D centroid = test.centroid();
    float dir = test.direction(centroid);

    //compute the transformation
    return ImageTransform(centroid,dir);
}

int main(){
    //read the image
    Image test(imread("data/test.png",0));
	Image fitted(test.rows,test.cols);

	//read the model
	Model model("models/otto");

	//draw initial state
	model.computeSamples();
	draw(test,fitted,model);

	//extract image Points
	vector<Point2D>imgPoints;
	test.highPass(0.3);
	test.extractPoints(imgPoints);

	//roughly align the model to the image
	ImageTransform transformation = getImageTransform(test);
	model.apply(transformation); //WARING HERE the model should has no transformation ( centered and vertical )

	//redraw
	model.computeSamples();
	draw(test,fitted,model);

	return 0;

	/*



	//draw
	model.computePoints();
	fitted.drawPoints(model.points);
	fitted.setDataRange(0,1);
	imshow("test",test.toColorMat(DISPLAY_SCALE));
	imshow("fitted",fitted.toColorMat(DISPLAY_SCALE));
	waitKey(0);
	fitted.reset();

	while(1){
		//initialize the forces vector
		vector<Point2D> forces;
		vector<float> count;
		for(size_t i = 0; i < model.points.size(); i++){
			forces.push_back(Point2D(0,0));
			count.push_back(0);
		}

		for(size_t i = 0; i < model.points.size(); i++){
			//find the closest point
			int winner = 0;
			float bestDistance = distance(imgPoints[0],model.points[i]);
			for(uint j = 1;j < imgPoints.size();++j){
				float dist = distance(imgPoints[j],model.points[i]);
				if(dist < bestDistance){
					winner = j;
					bestDistance = dist;
				}
			}

			model.points[i] = imgPoints[winner];
		}
		model.computeGenerators();
		model.computePoints();

		fitted.drawPoints(model.points);
		fitted.setDataRange(0,1);

		imshow("test",test.toColorMat(DISPLAY_SCALE));
		imshow("fitted",fitted.toColorMat(DISPLAY_SCALE));

		waitKey(0);

		fitted.reset();

	}

*/

/*	float data[] = {0,1,1,0,1,0};

	Mat A(Size(3,2),CV_32FC1,data);
	Mat B = A.inv(DECOMP_SVD);

	cout << B << endl;

	cout << A*B << endl;
	cout << B*A << endl;
*/
/*	Image test(40,40);

	for(int i = 0; i < 500;i++){
		test.add(randRange(-1.0f,1.0f),randRange(-1.0f,1.0f),0.7f);
	}

	Point2D centroid = test.centroid();

	cout << centroid[0] << " " << centroid[1] << endl;
	cout << test.direction(centroid)*RAD_TO_DEG << endl;

	imshow("test",test.toColorMat(10));
	waitKey(0);
*/
/*	Image test(imread("data/test.png",0));

	Point2D center = test.centroid();

	cout << center[0] << " " << center[1] << endl;

	float dir = test.direction(center);

	cout << "Direction " << dir*180.0/3.14159 << endl;

	float DISPLAY_SCALE = 10.0f;
	Mat drawing = test.toColorMat(DISPLAY_SCALE);

	float dx = cos(dir);
	float dy = sin(dir);

	float radius = drawing.cols/4;

	line(drawing,Point(center[0]*DISPLAY_SCALE - radius*dx,center[1]*DISPLAY_SCALE- radius*dy),Point(center[0]*DISPLAY_SCALE+ radius*dx,center[1]*DISPLAY_SCALE+ radius*dy),Scalar(0,0,255),2);

	imshow("drawing",drawing);

	waitKey(0);
*/
/*

	MNIST mnist("data/train-images","data/train-labels");

	for(int i = 0;true;i++){
		Image test(mnist.getImage(i));

		test.highPass(0.5);

		Image blur(5,5,{ 1, 1, 2, 1, 1,
		                 1, 3, 5, 3, 1,
					     2, 5, 7, 5, 2,
						 1, 3, 5, 3, 1,
					     1, 1, 2, 1, 1 });
	 	blur.normalize();

		Image convolved(test.rows,test.cols);

		test.convolve(blur,convolved);
		//convolved.setDataRange(0,1);


		//test.highPass(0.5);



		Mat gui = test.toColorMat(10);


		float dx = cos(alpha);
		float dy = sin(alpha);

		line(gui,Point(center[0]*DISPLAY_SCALE - radius*dx,center[1]*3.0f- 300*dy),Point(center[0]*3.0f+ 300*dx,center[1]*3.0f+ 300*dy),Scalar(0,0,255),2);

		dx = cos(beta);
		dy = sin(beta);

		line(gui,Point(center[0]*3.0f - 300*dx,center[1]*3.0f- 300*dy),Point(center[0]*3.0f+ 300*dx,center[1]*3.0f+ 300*dy),Scalar(0,255,0),2);
		*/
		/*
		dx = cos(dir);
			dy = sin(dir);

			line(gui,Point(center[0]*3.0f - 300*dx,center[1]*3.0f- 300*dy),Point(center[0]*3.0f+ 300*dx,center[1]*3.0f+ 300*dy),Scalar(0,0,255),2);
		*/
		/*
		Image kernel(3,5,{-2,-2,-2,-2,-2,
		                  -2, 2, 5, 2,-2,
					      -3, 3, 7, 3,-3 });

		Image convolved(test.rows,test.cols);

		test.setDataRange(-1,1);
		test.convolve(kernel,convolved);
		convolved.setDataRange(0,1);
		*/

		/*
		Image direction(test.rows,test.cols);
		Image intensity(test.rows,test.cols);

		test.gradient(direction,intensity);
		intensity.setDataRange(-1,1);
		direction.setDataRange(0,1);
		*/


		/*
		imshow("test",gui);
		imshow("borders",convolved.toColorMat(10));
		//imshow("borders",intensity.toColorMat(30));
		//imshow("direction",direction.toColorMat(30));

		waitKey(0);
	}
	*/
}
