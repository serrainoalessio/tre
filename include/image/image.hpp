#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <opencv2/core/core.hpp>
#include "geometry.hpp"

#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision

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
	Image(int _rows,int _cols,float* _data);

	void setData(float* ptr);
	void reset();

	//operator to both get and set the value of a pixel (x,y)
	float& operator() (int x,int y);
	float& operator[] (uint i);

	float operator() (int x,int y) const;
	float operator[] (uint i) const;

	//map coordinates from image to euclidean plane [-1,1]x[-1,1]
	void imgToEuclidean(float& x,float& y) const;
	void euclideanToImg(float& x,float& y) const;


	//linear interpolated get and set functions
	float get(float x,float y);
	void add(float x,float y,float v);

	//size comparision with other images
	bool hasSize(const Image& other) const;
	bool hasSize(uint _rows,uint _cols) const;

	std::pair<float,float> getDataRange() const;
	void getDataRange(float& min, float& max) const;
	//remap the pixel values into given range, return false it was impossible to remap the values
	bool setDataRange(float min, float max);
	//get the norm of the image ( the sum of all the pixel values)
	float norm() const;
	//set the norm of the image to 1
	bool normalize();

	//multi pixel functions
	void convolve(const Image& kernel,Image& destination) const;

	//single pixel functions
	void abs();
	void highPass(float v,bool keepValue = false);
	void lowPass(float v,bool keepValue = false);


	Point2D centroid() const;
	float direction(Point2D center) const;
	void gradient(Image& direction,Image& intensity) const;

	void extractPoints(vector<Point2D>& points) const;
	void drawPoints(vector<Point2D>& points);

	//operators
	Image& operator *= (float k);
	Image& operator /= (float k);

	void multiply(const Image& b,Image& dst);
	void invert(Image& dst);



	//convert the image to opencv Matrix ( actually it just wrap an opencv matrix around the data )
	cv::Mat toMat() const;
	//convert the image to an 8-bit 3-channels rgb image, it allow to upscale the resulting image
	cv::Mat toColorMat(int upscale = 1) const;
};

std::ostream& operator << (std::ostream &os, const Image &img);

#endif
