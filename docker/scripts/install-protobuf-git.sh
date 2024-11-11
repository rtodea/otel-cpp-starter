#!/bin/bash

# Save the current directory
PREVIOUS_DIRECTORY=$(pwd)

cd roll-dice/libraries || { echo "Directory roll-dice/libraries does not exist. ${CURRENT_DIR}" ; exit 1; }
git clone https://github.com/protocolbuffers/protobuf.git
cd protobuf
git checkout v28.3
git submodule update --init --recursive

# Installing via Bazel
# bazel build :protoc :protobuf
# cp bazel-bin/protoc /usr/local/bin

# Installing via CMake?
mkdir build
cd build
cmake .. -DCMAKE_CXX_STANDARD=14
cmake --build .

cd $PREVIOUS_DIRECTORY