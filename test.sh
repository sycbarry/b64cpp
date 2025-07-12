#!/bin/bash

rm -rf build
mkdir build
cd build && cmake ..
make
./test_b64cpp
# sudo make install
