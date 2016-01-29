#ifndef LOCK_FREE_VECTOR
#define LOCK_FREE_VECTOR


#include <atomic>
#include "misc.hpp"

#include <iostream>

using namespace std;


template< class T > class LockFreeVector{
private:
    T* data = NULL;
    atomic<int> _size {0};
    const int maxSize;
public:
    LockFreeVector(int count):maxSize(count){
        data = new T[maxSize];
    }

    T& operator[] (int i){
        return data[i];
    }

    void push_back(T el){
        if(_size < maxSize){
            data[_size] = el;
            _size++;
        }else{
            cerr << CONSOLE_RED << "Error lock free vector is full" << CONSOLE_RESET << endl;
        }
    }

    int size() const{
        return _size;
    }

    bool empty(){
        return _size == 0;
    }


    void clear(){
        _size = 0;
    }

    ~LockFreeVector(){
        delete[] data;
    }

};

#endif
