/*
 *   IMAGE TEST CODE GOES HERE
 */

#include "image/image.h"

int main(){
	Image test(200,200);

	imshow("test",test.toMat());
	waitkey(0);
}
