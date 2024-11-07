#!/bin/bash

cd roll-dice/libraries

# install `google-test` system wide ?

# install `benchmark` system wide ?

# install system-wide `oatpp` libary
git clone https://github.com/oatpp/oatpp.git
cd oatpp
git checkout 1.3.0-latest
mkdir build
cd build
cmake ..
make

# install open-telemetry
git clone https://github.com/open-telemetry/opentelemetry-cpp.git
cd opentelemetry-cpp
mkdir build
cd build
cmake -DBUILD_TESTING=OFF ..
cmake --build .
cmake --install . --prefix ../../otel-cpp
