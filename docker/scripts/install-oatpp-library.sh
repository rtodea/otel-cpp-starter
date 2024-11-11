#!/bin/bash

# Save the current directory
PREVIOUS_DIR=$(pwd)
echo "Current directory: $PREVIOUS_DIR"
LIB_DIR=/tmp/libraries
cd $LIB_DIR || { echo "Directory ${LIB_DIR} does not exist. ${CURRENT_DIR}" ; exit 1; }

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
cd $PREVIOUS_DIR
echo "Reverted back to the original directory: $PREVIOUS_DIR"
