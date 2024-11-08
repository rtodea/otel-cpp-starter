#!/bin/bash

# Save the current directory
CURRENT_DIR=$(pwd)
cd roll-dice/libraries || { echo "Directory roll-dice/libraries does not exist. ${CURRENT_DIR}" ; exit 1; }

# install open-telemetry
git clone https://github.com/open-telemetry/opentelemetry-cpp.git
cd opentelemetry-cpp
mkdir build
cd build
cmake -DBUILD_TESTING=OFF -DWITH_OTLP_HTTP=ON ..
cmake --build .
cmake --install . --prefix ../../otel-cpp
cd $CURRENT_DIR