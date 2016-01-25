/*
 *   IMAGE TEST CODE GOES HERE
 */

#include "image/image.hpp"
#include "dataset/dataset.hpp"

#include "misc.hpp"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(){
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

		/*
		test.reduceX(1);
		test.reduceX(-1);

		test.reduceY(1);
		test.reduceY(-1);
		*/

		/*
		Point2D center = test.centroid();

		cout << center[0] << " " << center[1] << endl;

		float alpha,beta;
		float dir = test.direction(center,alpha,beta);

		cout << "Direction " << dir*180.0/3.14159 << endl;
		*/

		Mat gui = test.toColorMat(10);

		/*
		float dx = cos(alpha);
		float dy = sin(alpha);

		line(gui,Point(center[0]*3.0f - 300*dx,center[1]*3.0f- 300*dy),Point(center[0]*3.0f+ 300*dx,center[1]*3.0f+ 300*dy),Scalar(0,0,255),2);

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



		imshow("test",gui);
		imshow("borders",convolved.toColorMat(10));
		//imshow("borders",intensity.toColorMat(30));
		//imshow("direction",direction.toColorMat(30));

		waitKey(0);
	}
}
