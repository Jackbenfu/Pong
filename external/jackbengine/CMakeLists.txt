cmake_minimum_required(VERSION 3.9)
project(jackbengine)

# CMake configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# SDL2 include directories
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})

# SDL2 library references
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Jackbengine include directories
include_directories(${PROJECT_SOURCE_DIR}/external)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Jackbengine source files
set(SOURCE_FILES
    external/easywsclient/easywsclient.cpp
    external/tinyxml/tinystr.cpp
    external/tinyxml/tinyxml.cpp
    external/tinyxml/tinyxmlerror.cpp
    external/tinyxml/tinyxmlparser.cpp
    src/application/abstract/abstractApplication.cpp
    src/application/application.cpp
    src/component/audio/audioSourceComponent.cpp
    src/component/body/shape/boxShapeComponent.cpp
    src/component/body/transformComponent.cpp
    src/component/body/velocityComponent.cpp
    src/component/input/mouseListenerComponent.cpp
    src/component/layout/containerComponent.cpp
    src/component/layout/zOrderComponent.cpp
    src/component/misc/nameComponent.cpp
    src/component/misc/tagComponent.cpp
    src/component/view/colorComponent.cpp
    src/component/view/spriteComponent.cpp
    src/component/view/textComponent.cpp
    src/component/generic/stringComponent.cpp
    src/core/sdl/io/sdlRwops.cpp
    src/core/sdl/surface/sdlSurface.cpp
    src/core/audio/sound.cpp
    src/core/audio/sound.impl.cpp
    src/core/input/input.cpp
    src/core/input/input.impl.cpp
    src/core/render/color32.cpp
    src/core/render/cursor/cursor.cpp
    src/core/render/cursor/cursor.impl.cpp
    src/core/render/font/defaultFont.cpp
    src/core/render/font/font.cpp
    src/core/render/font/font.impl.cpp
    src/core/render/renderer/renderer.cpp
    src/core/render/renderer/renderer.impl.cpp
    src/core/render/texture/texture.cpp
    src/core/render/texture/texture.impl.cpp
    src/core/render/window/window.cpp
    src/core/render/window/window.impl.cpp
    src/core/state/stateMachine.cpp
    src/core/time/timer.cpp
    src/core/time/timer.impl.cpp
    src/core/tmx/tmxImage.cpp
    src/core/tmx/tmxLayer.cpp
    src/core/tmx/tmxMap.cpp
    src/core/tmx/tmxObject.cpp
    src/core/tmx/tmxObjectGroup.cpp
    src/core/tmx/tmxProperty.cpp
    src/core/tmx/tmxPropertyGroup.cpp
    src/core/tmx/tmxText.cpp
    src/core/tmx/tmxTileset.cpp
    src/entity/entityManager.cpp
    src/scene/scene.cpp
    src/scene/loader/tmxSceneLoader.cpp
    src/system/animation/motionSystem.cpp
    src/system/debug/debugProfileSystem.cpp
    src/system/debug/debugSpriteSystem.cpp
    src/system/debug/debugTextSystem.cpp
    src/system/input/mouseEventTriggerSystem.cpp
    src/system/physic/aabbCollisionSystem.cpp
    src/system/render/spriteRenderSystem.cpp
    src/system/render/textRenderSystem.cpp
    src/system/system.cpp
    src/system/systemManager.cpp
    ${PLATFORM_SOURCE_FILES}
)

add_library(jackbengine ${SOURCE_FILES})
target_link_libraries(jackbengine ${SDL2_LIBRARY})
target_link_libraries(jackbengine ${SDL2_IMAGE_LIBRARY})
target_link_libraries(jackbengine ${SDL2_TTF_LIBRARY})
target_link_libraries(jackbengine ${SDL2_MIXER_LIBRARY})
