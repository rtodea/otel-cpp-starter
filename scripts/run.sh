#!/bin/bash

LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:/usr/local/lib:/app/roll-dice/libraries/otel-cpp/lib" ./roll-dice/build/dice-server
