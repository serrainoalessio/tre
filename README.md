# TRE
Shape matching for character recognition

# Dependencies
* opencv 3
* SDL 2
* g++ 4.9
* cmake 3
* ...

# Installation
After getting all the dependencies
```
git clone https://github.com/serrainoalessio/tre.git
cd tre
./get-mnist.sh
cmake .
make
```

#File Format
Every line begins with a letter that indicates the element type, followed by element properties
```
p -> point
r -> rectangle
l -> line
b -> bezier curve
```
###Point
```
p <x> <y> <radius> <r> <g> <b> <draggable = false>
```
###Bezier curve
```
b <point indexes>...
```
for example
```
b 0 1 2 3
```
defines a bezier curve drawn using the first 4 points defined by the file
