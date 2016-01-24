#include "image/image.hpp"
#include "misc.hpp"
#include <cassert>
#include <iostream>
#include <utility>

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

Image::Image(int _rows,int _cols,initializer_list<float> _data):rows(_rows),cols(_cols){
	this->allocate();

	#if IMAGE_SAFE == 1
		assert(_data.size() == rows*cols);
	#endif

	std::copy(_data.begin(), _data.end(), data.get());
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

float& Image::operator[] (uint i){
	return data.get()[i];
}

float Image::operator() (int x,int y) const{
	#if IMAGE_SAFE == 1
		x = keepInRange<uint>(x,0,cols-1);
		y = keepInRange<uint>(y,0,rows-1);
	#endif

	return data.get()[y*cols+x];
}

float Image::operator[] (uint i) const{
	return data.get()[i];
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

bool Image::hasSize(const Image& other) const{
	return hasSize(other.rows,other.cols);
}

bool Image::hasSize(uint _rows,uint _cols) const{
	return rows == _rows && cols == _cols;
}

std::pair<float,float> Image::getDataRange() const{
	std::pair<float,float> res;
	getDataRange(res.first,res.second);
	return res;
}

void Image::getDataRange(float& min,float& max) const{
	min = FLT_MAX;
	max = FLT_MIN;

	for(uint i = 0;i < rows*cols;++i){
		float v = data.get()[i];
		if(v < min)min = v;
		if(v > max)max = v;
	}
}

bool Image::setDataRange(float min,float max){
	#if IMAGE_SAFE == 1
		assert(max > min);
	#endif

	float oldMin,oldMax;
	getDataRange(oldMin,oldMax);

	#if IMAGE_SAFE == 1
		if( (oldMax - oldMin) < 1e-30){
			std::cout << CONSOLE_RED << "ERROR cannot set data range of image because its min (" << oldMin << ") is (almost) equal its max (" << oldMax << ")" << CONSOLE_RESET << endl;
			return false;
		}
	#endif

	float s = (max - min)/(oldMax - oldMin);
	for(uint i = 0;i < rows*cols;++i)data.get()[i] = (data.get()[i] - oldMin)*s + min;

	return true;
}

// TODO: implement this with avx
void Image::convolve(const Image& kernel,Image& destination) const{
	#if IMAGE_SAFE == 1
		assert(hasSize(destination));
		assert(kernel.rows%2 == 1);
		assert(kernel.cols%2 == 1);
	#endif

	int ox = kernel.cols/2;
	int oy = kernel.rows/2;

	#if IMAGE_SAFE == 1
		for(uint j = 0;j < rows;++j)for(uint i = 0;i < cols;++i)
	#else //if not image safe doesn't compute the gradient for outes pixels ( getting a pixel out of bound is "undefined behaviour" )
		for(uint j = oy;j < rows-oy;++j)for(uint i = ox;i < cols-ox;++i)
	#endif
	{
		destination(i,j) = 0;
		for(int y = -oy;y <= oy;++y)for(int x = -ox;x <= ox;++x){
			destination(i,j) += (*this)(i+x,j+y) * kernel(x+ox,y+oy);
		}
	}
}

void Image::gradient(Image& direction,Image& intensity) const{
	#if IMAGE_SAFE == 1
		assert(hasSize(direction));
		assert(hasSize(intensity));
	#endif

	Image kernelX(1,3,{-1,0,1});
	Image kernelY(3,1,{-1,0,1});

	convolve(kernelX,direction);
	convolve(kernelY,intensity);

	//TODO: implement this with avx
	for(uint i = 0;i < rows*cols;++i){
		float dx = direction[i];
		float dy = intensity[i];

		direction[i] = atan2(dy,dx);
		intensity[i] = dx*dx + dy*dy;
	}
}

// TODO: implement this with avx
void Image::abs() {
	for(uint i = 0;i < rows*cols;++i)data.get()[i] = fabs(data.get()[i]);
}

// TODO: implement this with avx
Point2D Image::centroid() const{
	Point2DCentroid centroid;

	for(uint j = 0; j < rows; ++j)for(uint i = 0;i < cols; ++i){
		centroid.add(Point2D(i,j),this->operator()(i,j));
	}

	return centroid.get();
}

class AngleAverage{
public:
	float A,W;

	AngleAverage(){
		A = 0;
		W = 0;
	}

	void add(float a,float w){
		if(w == 0)return;

		if(a - A > M_PI/2)a -= M_PI;
		else if(A - a > M_PI/2)A -= M_PI;
		A = (W*A+w*a)/(W+w);

		if(A < 0)A += M_PI;

		W += w;
	}

	float getAverage(){
		return A;
	}

	float getWeight(){
		return W;
	}
};


float signed_sqrt(float x){
	if(x < 0){
		return -sqrt(-x);
	}else{
		return sqrt(x);
	}
}

// TODO: implement this with avx
float Image::direction(Point2D& center,float& alpha,float& beta) const{
	float a = 0;
	float b = 0;
	float c = 0;

	for(uint j = 0; j < rows; ++j)for(uint i = 0;i < cols; ++i){
		float w = this->operator()(i,j);
		if(w > 0){
			a += (i-center[0])*(i-center[0]);
			b += (i-center[0])*(j-center[1]);
			c += (j-center[1])*(j-center[1]);
		}
	}

	float nv = sqrt(c*c + b*b);
	float no = sqrt(a*a + b*b);

	Point2D Y(b/nv,c/nv);
	Point2D X(a/no,b/no);


	float k = signed_sqrt(Y[0]*X[0] + Y[1]*X[1]);
	//cout << "K: " << k << endl;

	beta = atan2(Y[1],Y[0]); // vertical component ( the most important)
	if(beta < 0)beta = M_PI + beta;

	alpha = atan2(X[1] -k*Y[1],X[0] -k*Y[0]);
	if(alpha < 0)alpha = M_PI + alpha;

/*
	float dist = fabs(alpha - beta);
	if(dist > M_PI/2){

	} dist = M_PI - dist;

	if(dist < M_PI/2){
		cout << "small" << endl;
	}
*/

	cout << a << " " << b << " " << c << endl;
	cout << (c*c+b*b)/(b*b+a*a) << endl;

	//if(beta-alpha > M_PI/2)alpha += M_PI/2;


	//alpha = atan2(2*b*(a+c),a*a+c*c)/2 + M_PI/2;


	AngleAverage avg;

	for(uint j = 0; j < rows; ++j)for(uint i = 0;i < cols; ++i){
		float w = this->operator()(i,j);
		avg.add(atan2(j-center[1],i-center[0]),w);
	}

	return avg.getAverage();
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
