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

		Image direction(test.rows,test.cols);
		Image intensity(test.rows,test.cols);

		test.gradient(direction,intensity);
		intensity.setDataRange(0,1);

		imshow("test",test.toColorMat(3));
		imshow("borders",intensity.toColorMat(3));


		waitKey(0);
	}
}
