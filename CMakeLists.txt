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

configure_file(resources/game_768x576.tmx game_768x576.tmx COPYONLY)
configure_file(resources/menu_768x576.tmx menu_768x576.tmx COPYONLY)
configure_file(resources/tileset.png tileset.png COPYONLY)

add_custom_command(
    OUTPUT resources.c
    COMMAND resourceGenerator
        resources.c
        ${PROJECT_SOURCE_DIR}/resources/left.wav
        ${PROJECT_SOURCE_DIR}/resources/right.wav
        ${PROJECT_SOURCE_DIR}/resources/wall.wav
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
