#!/usr/bin/env bash

mkdir data
cd data

wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
gzip -d train-labels-idx1-ubyte.gz
mv train-labels-idx1-ubyte train-labels
gzip -d train-images-idx3-ubyte.gz
mv train-images-idx3-ubyte train-images