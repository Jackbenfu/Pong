# Jackbengine
A multi-platform C++ 2D game engine.

## Features

#### Multi-platform
The engine runs and was successfully tested on the following platforms:
- OS X, macOS
- Windows (MinGW)
- Web (Emscripten)

#### ECS pattern implementation
Summary of the Entity-component-system approach:
- _Entities_ are made up of one or more components
- _Components_ contain data to store the state of an entity
- _Systems_ contain the logic and operate on entities that have the required components

The engine provides standard components and systems usually needed in a game:
* Components: `Transform`, `Velocity`, `BoxShape`, `Sprite`, `Text`, `MouseListener`, `AudioSource` etc.
* Systems: `Motion`, `SpriteRender`, `TextRender`, `MouseEventTrigger`, `AABBCollision`, `DebugProfile`, `DebugSprite` etc.

This collection of components and systems can be extended.

#### Scene management
- Scenes can be used to split the game in logical parts (menus, in-game, options etc.) and/or functional parts (levels, screens etc.).
- A scene has its own context and cannot interact with other scenes.
- Transitions between scenes is possible by loading a scene from the current one (the previous scene being automatically unloaded).

#### Resource management
- Resources can be loaded from files or embedded resources.
- Embedded resources can be generated using the [ResourceGenerator](https://github.com/Jackbenfu/ResourceGenerator) tool.

#### Tile Map XML basic support (see [official reference](http://doc.mapeditor.org/reference/tmx-map-format/))
* Current implementation supports loading of following nodes:
 * `Map`
 * `Tileset` (only one per file)
 * `Layer`
 * `Object` and `ObjectGroup`
 * `Property` and `Properties`
 * `Text`
 
#### WebSocket client
- The class `WebSocket` wraps a web socket connection and allows to bind one `deserializer` and one `callback` per typed network message.

## Development information
- All targets (except Web) are compiled using [CMake](https://cmake.org/).
- Web targets are compiled using [Emscripten](http://emscripten.org/) and Makefiles.
- My main IDE is [CLion](https://www.jetbrains.com/clion/), the powerfull cross-platform C/C++ IDE from JetBrains!

## External dependencies
The engine relies on the following awesome libraries and tools:
- [Emscripten](http://emscripten.org/)
- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
- [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
- [TinyXML](https://sourceforge.net/projects/tinyxml/)
- [easywsclient](https://github.com/dhbaird/easywsclient)
