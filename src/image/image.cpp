#include "image/image.hpp"
#include "misc.hpp"
#include <cassert>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;

//enable some safe checks lowering performances 
#define IMAGE_SAFE 1

Image::Image(cv::Mat&& src):rows(src.rows),cols(src.cols){
	this->allocate();

	//8-bit single channel image ( uchar in range 0-255)
	assert(src.type() == CV_8UC1);

	//copy and map range of the data
	float* ptr = this->data.get();
	for(uint i = 0;i < cols*rows;i++)ptr[i] = float(src.data[i])/255.0f;
}

Image::Image(cv::Mat& src):rows(src.rows),cols(src.cols){
	this->allocate();

	//8-bit single channel image ( uchar in range 0-255)
	assert(src.type() == CV_8UC1);

	//copy and map range of the data
	float* ptr = this->data.get();
	for(uint i = 0;i < cols*rows;i++)ptr[i] = float(src.data[i])/255.0f;
}

Image::Image(int _rows,int _cols):rows(_rows),cols(_cols){
	this->allocate();
}

void Image::allocate(){
	//allocate the image data 32-bit aligned to enable fast avx functions
	data.reset((float*)aligned_alloc(32, rows * cols * sizeof(float)));
}

float& Image::operator() (int x,int y){
	#if IMAGE_SAFE == 1
		x = keepInRange<uint>(x,0,cols-1);
		y = keepInRange<uint>(y,0,rows-1);
	#endif

	return data.get()[y*cols+x];
}

float Image::get(float x,float y){
	float wx = x - floor(x);
	float wy = y - floor(y);
	float v = 0;

	v += (*this)(floor(x),floor(y))*(1 - wx)*(1 - wy);
	v += (*this)( ceil(x), ceil(y))*(    wx)*(    wy);
	v += (*this)(floor(x), ceil(y))*(1 - wx)*(    wy);
	v += (*this)( ceil(x),floor(y))*(    wx)*(1 - wy);

	return v;
}

void Image::add(float x,float y,float v){
	float wx = x - floor(x);
	float wy = y - floor(y);

	(*this)(floor(x),floor(y)) += v*(1 - wx)*(1 - wy);
	(*this)( ceil(x), ceil(y)) += v*(    wx)*(    wy);
	(*this)(floor(x), ceil(y)) += v*(1 - wx)*(    wy);
	(*this)( ceil(x),floor(y)) += v*(    wx)*(1 - wy);
}

cv::Mat Image::toMat() const{
	return cv::Mat(rows, cols,CV_32FC1,data.get());
}

cv::Mat Image::toColorMat(int upscale) const{
	Mat res(rows,cols,CV_8UC3);

	for(uint j = 0; j < rows; ++j)for(uint i = 0;i < cols; ++i){
		res.data[(j*cols+i)*3 + 0] = (uchar)(data.get()[j*cols+i]*255.0f);
		res.data[(j*cols+i)*3 + 1] = (uchar)(data.get()[j*cols+i]*255.0f);
		res.data[(j*cols+i)*3 + 2] = (uchar)(data.get()[j*cols+i]*255.0f);
	}

	if(upscale > 1){
		Mat big;
		resize(res,big,Size(),upscale,upscale,INTER_NEAREST);
		return big;
	}

	return res;
}