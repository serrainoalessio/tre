#ifndef MNIST_H
#define MNIST_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

class MNIST{
	ifstream imagesFile;
	const static unsigned imagesFileOffset = 4*sizeof(int);
	int imageCount;
	int imageRows;
	int imageCols;

	ifstream labelFile;
	const static unsigned labelFileOffset = 2*sizeof(int);
	int labelCount;

public:
	MNIST(string imagesPath,string labelsPath);

	Mat getImage(int i = 0);
	int getLabel(int i = 0);

	int count();
};

#endif