#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <opencv2/core/core.hpp>

using namespace std;

class Image{
private:
	void allocate();

	//matrix data saved in row major order
	shared_ptr<float> data;

public:
	const unsigned int rows = 0;
	const unsigned int cols = 0;

	Image();
	Image(cv::Mat& img);
	Image(int _rows,int _cols);


	//operator to both get and set the value of a pixel (x,y)
	float& operator() (int x,int y);

	//linear interpolated get and set functions
	float get(float x,float y);
	void add(float x,float y,float v);

	/*
	//make sure that the image has the given size
	void ensureSize(FloatImage& o);
	void ensureSize(int _rows,int _cols);
	*/

	//remap the pixel values into given range, return false it was impossible to remap the values
	bool setDataRange(float min,float max);

	//convert the image to opencv Matrix ( actually it just wrap an opencv matrix around the data )
	cv::Mat toMat() const;

};

#endif