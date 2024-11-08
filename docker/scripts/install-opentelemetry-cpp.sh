#!/bin/bash

# Save the current directory
CURRENT_DIR=$(pwd)
echo "Current directory: $CURRENT_DIR"
exit 0

cd roll-dice/libraries

# install open-telemetry
git clone https://github.com/open-telemetry/opentelemetry-cpp.git
cd opentelemetry-cpp
mkdir build
cd build
cmake -DBUILD_TESTING=OFF ..
cmake --build .
cmake --install . --prefix ../../otel-cpp
cd $CURRENT_DIR