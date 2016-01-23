#include "dataset/mnist.hpp"
#include "misc.hpp"
#include <algorithm>

template <class T>
void endswap(T *objp)
{
  unsigned char *memp = reinterpret_cast<unsigned char*>(objp);
  std::reverse(memp, memp + sizeof(T));
}


MNIST::MNIST(string imagesPath,string labelsPath):imagesFile(imagesPath,ios::binary),labelFile(labelsPath,ios::binary){
	if(!imagesFile.is_open()){
		cout << CONSOLE_RED << "ERROR file '" << imagesPath << "' doesn't exists" << CONSOLE_RESET << endl;
		throw exception();
	}
	if(!labelFile.is_open()){
		cout << CONSOLE_RED << "ERROR file '" << labelsPath << "' doesn't exists" << CONSOLE_RESET << endl;
		throw exception();
	}

	imagesFile.seekg(4);
	imagesFile.read((char*)&imageCount,sizeof(int));
	imagesFile.read((char*)&imageRows,sizeof(int));
	imagesFile.read((char*)&imageCols,sizeof(int));

	//convert from high endian to little endian
	endswap(&imageCount);
	endswap(&imageRows);
	endswap(&imageCols);

	labelFile.seekg(4);
	labelFile.read((char*)&labelCount,sizeof(int));

	//convert from high endian to little endian
	endswap(&labelCount);

	if(imageCount != labelCount){
		cout << CONSOLE_YELLOW << "WARNING mnist files has " << imageCount << " images and " << labelCount << "labels" << endl;
		cout << "Probably you are mixing training and test sets" << CONSOLE_RESET << endl;  
	}
}

Mat MNIST::getImage(int i){
	i = keepInRange(i,0,imageCount);

	Mat A(imageCols,imageRows,CV_8UC1);
	uchar* ptr = A.data;


	imagesFile.seekg(imagesFileOffset + (i*imageCols*imageRows));
	imagesFile.read((char*)ptr,sizeof(char)*imageCols*imageRows);

	if(unlikely(imagesFile.eof() || imagesFile.bad())){
		cout << CONSOLE_RED << "Error reading MNIST image " << i << CONSOLE_RESET << endl;
	}

	return A;
}

int MNIST::getLabel(int i){
	i = keepInRange(i,0,labelCount);

	uchar c;
	labelFile.seekg(labelFileOffset + i);
	labelFile.read((char*)&c,1);

	if(unlikely(labelFile.eof() || labelFile.bad())){
		cout << CONSOLE_RED << "Error reading MNIST label " << i << CONSOLE_RESET << endl;
	}

	return (int)c;
}

int MNIST::count(){
	return imageCount;
}