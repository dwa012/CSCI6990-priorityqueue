#!/bin/bash
cd gtest-1.6.0
./configure
mkdir lib
cd lib
cmake ..
make
cd ../..

