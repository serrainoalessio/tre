/*
 *   IMAGE TEST CODE GOES HERE
 */

#include "image/image.hpp"
#include "misc.hpp"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(){
	Image test(300,300);

	for (int i = 0; i < 50000; ++i){
		float x = randRange<float>(0,test.rows);
		float y = randRange<float>(0,test.cols);

		test.add(x,y,0.5);
	}

	imshow("test",test.toMat());
	waitKey(0);
}
