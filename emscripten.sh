#!/usr/bin/env bash

pwd=`pwd`

# Building Jackbengine library
cd ${pwd}/external/jackbengine
make -f Makefile.emscripten
cd -

# Building Resource generator tool
cd ${pwd}/external/resourceGenerator
make -f Makefile.emscripten
cd -

# Generating resources.cpp
./external/resourceGenerator/resourceGenerator             \
    resources.cpp                                          \
    -bresources/left.wav                                   \
    -bresources/right.wav                                  \
    -bresources/wall.wav                                   \
    -tresources/menu.tmx                                   \
    -tresources/wall.tmx                                   \
    -tresources/two_players.tmx                            \
    -tresources/one_player.tmx                             \
    -bresources/tileset.png

# Building Pong web output
make -f Makefile.emscripten
