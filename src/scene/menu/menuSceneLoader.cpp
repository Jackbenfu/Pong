//
// menuSceneLoader.cpp
// Pong
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright © 2016 Damien Bendejacq. All rights reserved.
//

#include "menuSceneLoader.h"

IMPORT_BINARY_RESOURCE(tileset_png)

MenuSceneLoader::MenuSceneLoader(Scene *scene)
    : TmxSceneLoader(scene)
{
}

MenuSceneLoader::~MenuSceneLoader() = default;

bool MenuSceneLoader::loadContents()
{
    addResourceDependency(TILESET_FILE, tileset_png, tileset_png_size);

    createImageEntityFromLayer("background", TILESET_FILE);
    createTextEntityFromObject("menu", "title");
    createTextEntityFromObject("menu", "play");
#ifndef EMSCRIPTEN
    createTextEntityFromObject("menu", "quit");
#endif
    createTextEntityFromObject("about", "author");

    auto spriteRenderSystem = scene()->addSystem<SpriteRenderSystem>();
    spriteRenderSystem->setRenderer(scene()->renderer());

    auto textRenderSystem = scene()->addSystem<TextRenderSystem>();
    textRenderSystem->setRenderer(scene()->renderer());

    auto mouseEventTriggerSystem = scene()->addSystem<MouseEventTriggerSystem>();
    mouseEventTriggerSystem->setInput(scene()->input());

    return true;
}
