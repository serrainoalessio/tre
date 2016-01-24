#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <opencv2/core/core.hpp>
#include "geometry.hpp"

using namespace std;

class Image{
private:
	void allocate();

	//matrix data saved in row major order
	shared_ptr<float> data;

public:
	const uint rows = 0;
	const uint cols = 0;

	Image();
	Image(cv::Mat&& img);
	Image(cv::Mat& img);
	Image(int _rows,int _cols);
	Image(int _rows,int _cols,initializer_list<float> _data);

	//operator to both get and set the value of a pixel (x,y)
	float& operator() (int x,int y);
	float& operator[] (uint i);

	float operator() (int x,int y) const;
	float operator[] (uint i) const;

	//linear interpolated get and set functions
	float get(float x,float y);
	void add(float x,float y,float v);

	//size comparision with other images
	bool hasSize(const Image& other) const;
	bool hasSize(uint _rows,uint _cols) const;

	std::pair<float,float> getDataRange() const;
	void getDataRange(float& min,float& max) const;
	//remap the pixel values into given range, return false it was impossible to remap the values
	bool setDataRange(float min,float max);

	//convolution filters
	void convolve(const Image& kernel,Image& destination) const;

	void gradient(Image& direction,Image& intensity) const;

	void abs();

	Point2D centroid() const;
	float direction(Point2D& center) const;

	//convert the image to opencv Matrix ( actually it just wrap an opencv matrix around the data )
	cv::Mat toMat() const;
	//convert the image to an 8-bit 3-channels rgb image, it allow to upscale the resulting image
	cv::Mat toColorMat(int upscale = 1) const;
};

#endif
