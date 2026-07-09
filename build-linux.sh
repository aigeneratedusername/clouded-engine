#!/bin/bash
cmake --preset Linux -B build-linux -DCMAKE_BUILD_TYPE=Debug
cmake --build build-linux
./build-linux/bin/clouded-engine
