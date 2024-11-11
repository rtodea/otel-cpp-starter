#!/bin/bash

cd roll-dice

rm -rf build
mkdir build
cd build

cmake ..
cmake --build .

