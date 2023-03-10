#!/bin/sh

# Check CMake
if ! type cmake &> /dev/null;
then
    echo "Cmake not installed. Install and run again"
    exit 1
fi

mkdir build
cd build/

cmake ../ && cmake --build . 