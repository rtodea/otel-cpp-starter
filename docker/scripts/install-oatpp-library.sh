#!/bin/bash

# Save the current directory
CURRENT_DIR=$(pwd)

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

# Revert back to the original directory
cd $CURRENT_DIR
