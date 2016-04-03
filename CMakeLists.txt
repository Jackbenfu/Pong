cmake_minimum_required(VERSION 3.5)
project(pong)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
#    resources/game_768x576.tmx
#    resources/left.wav
#    resources/menu_768x576.tmx
#    resources/pong.icns
#    resources/pong.ico
#    resources/pong.plist
#    resources/right.wav
#    resources/tileset.png
#    resources/Volter__28Goldfish_29.ttf
#    resources/wall.wav
    src/main.cpp
    src/pongApp.cpp
    src/pongApp.h
    src/pongGame.cpp
    src/pongGame.h
    src/pongMenu.cpp
    src/pongMenu.h)

add_executable(pong ${SOURCE_FILES})
