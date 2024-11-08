#!/bin/bash

cd roll-dice/libraries

# install open-telemetry
git clone https://github.com/open-telemetry/opentelemetry-cpp.git
cd opentelemetry-cpp
mkdir build
cd build
cmake -DBUILD_TESTING=OFF ..
cmake --build .
cmake --install . --prefix ../../otel-cpp
