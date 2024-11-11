#!/bin/bash

# Save the current directory
PREVIOUS_DIRECTORY=$(pwd)
LIB_DIR=/tmp/libraries
cd $LIB_DIR || { echo "Directory ${LIB_DIR} does not exist. ${CURRENT_DIR}" ; exit 1; }
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
cmake .. \
  -DCMAKE_CXX_STANDARD=14 \
  -Dprotobuf_LIBPROTOBUF=ON \
  -Dprotobuf_BUILD_TESTS=OFF \
  -Dprotobuf_BUILD_EXAMPLES=OFF \
  -Dprotobuf_BUILD_SHARED_LIBS=ON
cmake --build . -j $(nproc)
cmake --install .

# also installing the `absl` library
# cd third_party/abseil-cpp
# make install

cd $PREVIOUS_DIRECTORY