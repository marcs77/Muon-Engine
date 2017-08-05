#!/bin/sh
mkdir build
cd build
cmake .. $* -DCMAKE_BUILD_TYPE=Debug -DBUILD_GAME=testgame -G"CodeLite - Unix Makefiles"
