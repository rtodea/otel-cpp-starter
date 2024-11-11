#!/bin/bash

PREVIOUS_DIR=$(pwd)
LIB_DIR=/tmp/libraries
cd $LIB_DIR || { echo "Directory ${LIB_DIR} does not exist. ${PREVIOUS_DIR}" ; exit 1; }

# install open-telemetry
git clone https://github.com/open-telemetry/opentelemetry-cpp.git
cd opentelemetry-cpp
mkdir build
cd build
cmake -DBUILD_TESTING=OFF \
  -DWITH_OTLP_HTTP=ON \
  -DWITH_ABSEIL=ON \
  ..

cmake --build . -j $(nproc)
cmake --install . --prefix ../../otel-cpp
cd $PREVIOUS_DIR
