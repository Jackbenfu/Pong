cmake_minimum_required(VERSION 3.5)
project(pong)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Using Jackbengine library
add_subdirectory(${PROJECT_SOURCE_DIR}/external/jackbengine)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/include)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/src)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/external)

configure_file(resources/game_768x576.tmx game_768x576.tmx COPYONLY)
configure_file(resources/left.wav left.wav COPYONLY)
configure_file(resources/menu_768x576.tmx menu_768x576.tmx COPYONLY)
configure_file(resources/right.wav right.wav COPYONLY)
configure_file(resources/tileset.png tileset.png COPYONLY)
configure_file(resources/Volter__28Goldfish_29.ttf Volter__28Goldfish_29.ttf COPYONLY)
configure_file(resources/wall.wav wall.wav COPYONLY)

set(SOURCE_FILES
    src/main.cpp
    src/pongApp.cpp
    src/pongGame.cpp
    src/pongMenu.cpp
)

add_executable(pong ${SOURCE_FILES})
target_link_libraries(pong jackbengine)
