//
//  pongMenu.cpp
//  Pong
//
//  Created by Damien Bendejacq on 27/07/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#include "pongMenu.h"

IMPORT_BINARY_RESOURCE(default_font)
IMPORT_BINARY_RESOURCE(tileset_png)
IMPORT_TEXT_RESOURCE(menu_768x576_tmx)

PongMenu::PongMenu()
{
}

PongMenu::~PongMenu()
{
    DELETE_SAFE(m_tmxLoader);
}

void PongMenu::frame(float delta)
{
    UNUSED(delta);

    // Nothing to do each frame!
}

const char* PongMenu::name()
{
    return "menu";
}

void PongMenu::onPlayClick(void *data)
{
    UNUSED(data);

    loadScene("game");
    cursor()->setCursor(CursorType::Default);
}

void PongMenu::onQuitClick(void *data)
{
    UNUSED(data);

    exit();
}

void PongMenu::onButtonEnter(void *data)
{
    auto button = static_cast<Entity*>(data);

    auto text = GET_COMPONENT(button, TextComponent);
    if (text)
    {
        text->setForeground(Color_YellowGold);
    }

    cursor()->setCursor(CursorType::Hand);
}

void PongMenu::onButtonExit(void *data)
{
    auto button = static_cast<Entity*>(data);

    auto text = GET_COMPONENT(button, TextComponent);
    if (text)
    {
        text->setForeground(Color_White);
    }

    cursor()->setCursor(CursorType::Default);
}

bool PongMenu::initContents()
{
    m_tmxLoader = new TmxSceneLoader(this);
    m_tmxLoader->addResourceDependency("tileset.png", tileset_png, tileset_png_size);
    m_tmxLoader->loadFromMemory(menu_768x576_tmx);

    {
        auto playButton = m_tmxLoader->getEntity("play");
        auto mouseListener = ADD_COMPONENT(playButton, MouseListenerComponent);
        mouseListener->onLeftClick(onPlayClick);
        mouseListener->onEnter(onButtonEnter, playButton);
        mouseListener->onExit(onButtonExit, playButton);
    }

    {
        auto quitButton = m_tmxLoader->getEntity("quit");
#ifndef EMSCRIPTEN
        auto mouseListener = ADD_COMPONENT(quitButton, MouseListenerComponent);
        mouseListener->onLeftClick(onQuitClick);
        mouseListener->onEnter(onButtonEnter, quitButton);
        mouseListener->onExit(onButtonExit, quitButton);
#else
        DISABLE_ENTITY(quitButton);
#endif
    }

    auto debugProfileSystem = ADD_SYSTEM(DebugProfileSystem);
    debugProfileSystem->setRenderer(renderer());
    debugProfileSystem->setTimer(timer());

    return true;
}
