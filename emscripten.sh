#!/usr/bin/env bash

pwd=`pwd`

# Building Jackbengine library
cd ${pwd}/external/jackbengine
make -f Makefile.emscripten
cp libjackbengine.bc ../..
cd -

# Building Resource generator tool
cd ${pwd}/external/resourceGenerator
make -f Makefile.emscripten
cp resourceGenerator ../..
cd -

# Generating resources.cpp
./resourceGenerator          \
    resources.cpp            \
    -bresources/left.wav     \
    -bresources/right.wav    \
    -bresources/wall.wav     \
    -bresources/tileset.png  \
    -tresources/menu.tmx     \
    -tresources/multi.tmx

# Building Pong web output
make -f Makefile.emscripten
