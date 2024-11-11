#!/bin/bash

# Save the current directory
PREVIOUS_DIRECTORY=$(pwd)

cd roll-dice/libraries || { echo "Directory roll-dice/libraries does not exist. ${CURRENT_DIR}" ; exit 1; }
git clone https://github.com/abseil/abseil-cpp.git
cd abseil-cpp
git checkout 20240722.0
git submodule update --init --recursive

# Installing via CMake?
mkdir build
cd build
cmake ..
cmake --build .
cmake --install .

cd $PREVIOUS_DIRECTORY