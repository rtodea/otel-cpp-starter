#!/bin/bash

# Save the current directory
PREVIOUS_DIRECTORY=$(pwd)
cd /tmp

VERSION=28.3 # Update this to the desired version
wget https://github.com/protocolbuffers/protobuf/releases/download/v$VERSION/protobuf-$VERSION.tar.gz
tar -xzf protobuf-$VERSION.tar.gz

cd protobuf-$VERSION
./configure --prefix=/usr/local
make -j$(nproc)
sudo make install
