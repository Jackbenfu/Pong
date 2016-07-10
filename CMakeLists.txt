cmake_minimum_required(VERSION 3.5)
project(pong)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "-mwindows")
endif(MINGW)

# Using Jackbengine library
add_subdirectory(${PROJECT_SOURCE_DIR}/external/jackbengine)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/include)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/src)
include_directories(${PROJECT_SOURCE_DIR}/external/jackbengine/external)

# Using Resource generator tool
add_executable(
    resourceGenerator
    ${PROJECT_SOURCE_DIR}/external/resourceGenerator/resourceGenerator.cpp
)

# Creating resources C representations
add_custom_command(
    OUTPUT resources.cpp
    COMMAND resourceGenerator
        resources.cpp
        -b${PROJECT_SOURCE_DIR}/resources/left.wav
        -b${PROJECT_SOURCE_DIR}/resources/right.wav
        -b${PROJECT_SOURCE_DIR}/resources/wall.wav
        -t${PROJECT_SOURCE_DIR}/resources/menu_768x576.tmx
        -t${PROJECT_SOURCE_DIR}/resources/game_768x576.tmx
        -b${PROJECT_SOURCE_DIR}/resources/tileset.png
        -b${PROJECT_SOURCE_DIR}/resources/pong32x32.png
)

# Tell CMake to create an app bundle on MacOS
if(APPLE)
    set(CMAKE_MACOSX_BUNDLE true)
    set(ICON_FILE ${PROJECT_SOURCE_DIR}/resources/${CMAKE_PROJECT_NAME}.icns)
    set_source_files_properties(
        ${ICON_FILE}
        PROPERTIES
        MACOSX_PACKAGE_LOCATION
        Resources
    )
endif(APPLE)

if(MINGW)
    set(ICON_FILE ${PROJECT_SOURCE_DIR}/resources/win_icon.rc)
endif(MINGW)

# Defining source files
set(
    SOURCE_FILES
    src/main.cpp
    src/pongApp.cpp
    src/pongGame.cpp
    src/pongMenu.cpp
    resources.cpp
    ${ICON_FILE}
)

# Compiling final executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} jackbengine)

# Post build operations
if(APPLE)
    set_target_properties(
        ${CMAKE_PROJECT_NAME}
        PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST
        ${PROJECT_SOURCE_DIR}/resources/${CMAKE_PROJECT_NAME}.plist
    )
endif(APPLE)
