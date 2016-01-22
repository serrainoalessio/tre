#ifndef STOPWATCH_H
#define STOPWATCH_H 1

#include <chrono>
#include <iostream>
#include <string>

using namespace std;

class Stopwatch{
public:
	float time = 0; // total measured time
	int count = 0; // lap count
	bool started = false;
	string name;
	std::chrono::system_clock::time_point start;

	Stopwatch(string n = ""):name(n){} //initialize with a name

	void tick(){
		if(started){
			count++;
    		
    		auto end = std::chrono::system_clock::now();
    		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			//convert from nanoseconds to milliseconds
    		time += elapsed.count()/1000000.0;
		}else{
			start = std::chrono::system_clock::now();
		}
		started = !started;
	}
};

std::ostream &operator<<(std::ostream &os, Stopwatch const &watch) { 
    return os << watch.name << ":\n     time: " << watch.time << "ms\n     count: " << watch.count << "\n     average time: " << watch.time/watch.count << "ms" << endl;
}

#endif