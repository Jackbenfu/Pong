cmake_minimum_required(VERSION 3.5)
project(pong)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Using Jackbengine library
add_subdirectory(${PROJECT_SOURCE_DIR}/external/jackbengine)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/include)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/src)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/external)

# Using Resource generator tool
add_executable(
    resourceGenerator
    ${PROJECT_SOURCE_DIR}/external/resourceGenerator/resourceGenerator.c
)

add_custom_command(
    OUTPUT resources.c
    COMMAND resourceGenerator
        resources.c
        -b${PROJECT_SOURCE_DIR}/resources/left.wav
        -b${PROJECT_SOURCE_DIR}/resources/right.wav
        -b${PROJECT_SOURCE_DIR}/resources/wall.wav
        -t${PROJECT_SOURCE_DIR}/resources/menu_768x576.tmx
        -t${PROJECT_SOURCE_DIR}/resources/game_768x576.tmx
        -b${PROJECT_SOURCE_DIR}/resources/tileset.png
)

add_executable(
    pong
    src/main.cpp
    src/pongApp.cpp
    src/pongGame.cpp
    src/pongMenu.cpp
    resources.c
)
target_link_libraries(pong jackbengine)
