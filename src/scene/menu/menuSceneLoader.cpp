//
// menuSceneLoader.cpp
// Jackbengine
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright (c) 2016 Damien Bendejacq. All rights reserved.
//

#include "menuSceneLoader.h"

IMPORT_BINARY_RESOURCE(tileset_png)

MenuSceneLoader::MenuSceneLoader(Scene *scene)
    : TmxSceneLoader(scene)
{
}

MenuSceneLoader::~MenuSceneLoader()
{
}

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

    auto spriteRenderSystem = ADD_SYSTEM(SpriteRenderSystem);
    spriteRenderSystem->setRenderer(m_scene->renderer());

    auto textRenderSystem = ADD_SYSTEM(TextRenderSystem);
    textRenderSystem->setRenderer(m_scene->renderer());

    auto mouseEventTriggerSystem = ADD_SYSTEM(MouseEventTriggerSystem);
    mouseEventTriggerSystem->setInput(m_scene->input());

    return true;
}
