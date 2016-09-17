//
// menuSceneLoader.cpp
// Jackbengine
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright (c) 2016 Damien Bendejacq. All rights reserved.
//

#include "menuSceneLoader.h"

IMPORT_BINARY_RESOURCE(default_font)
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
    loadBackground();
    loadTitle();
    loadPlayButton();
#ifndef EMSCRIPTEN
    loadQuitButton();
#endif
    loadAuthorInfo();
    loadSystems();

    return true;
}

void MenuSceneLoader::loadBackground()
{
    auto background = ADD_ENTITY("background");

    ADD_COMPONENT(background, TransformComponent);
    ADD_COMPONENT(background, SpriteComponent)->loadFromLayer(
        m_scene->renderer(),
        map(),
        "background",
        tileset_png,
        tileset_png_size
    );
}

void MenuSceneLoader::loadTitle()
{
    auto object = map()->getObjectGroup("menu")->getObject("title");

    auto title = ADD_ENTITY("title");

    ADD_COMPONENT(title, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = ADD_COMPONENT(title, TextComponent);
    text->setText("PONG");
    text->setLayout(TextLayout::CenterCenter);
    text->setForeground(Color_White);
    text->setFontFromMemory(
        m_scene->renderer(),
        default_font,
        default_font_size,
        144
    );
}

void MenuSceneLoader::loadPlayButton()
{
    auto object = map()->getObjectGroup("menu")->getObject("play");

    auto play = ADD_ENTITY("play");

    ADD_COMPONENT(play, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = ADD_COMPONENT(play, TextComponent);
    text->setText("Play");
    text->setLayout(TextLayout::CenterCenter);
    text->setForeground(Color_White);
    text->setFontFromMemory(
        m_scene->renderer(),
        default_font,
        default_font_size,
        45
    );
}

void MenuSceneLoader::loadQuitButton()
{
    auto object = map()->getObjectGroup("menu")->getObject("quit");

    auto quit = ADD_ENTITY("quit");

    ADD_COMPONENT(quit, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = ADD_COMPONENT(quit, TextComponent);
    text->setText("Quit");
    text->setLayout(TextLayout::CenterCenter);
    text->setForeground(Color_White);
    text->setFontFromMemory(
        m_scene->renderer(),
        default_font,
        default_font_size,
        45
    );
}

void MenuSceneLoader::loadAuthorInfo()
{
    auto object = map()->getObjectGroup("about")->getObject("author");

    auto author = ADD_ENTITY("author");

    ADD_COMPONENT(author, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = ADD_COMPONENT(author, TextComponent);
    text->setText("Copyright (c) 2016 Jackben");
    text->setLayout(TextLayout::RightBottom);
    text->setForeground(Color_White);
    text->setFontFromMemory(
        m_scene->renderer(),
        default_font,
        default_font_size,
        18
    );
}

void MenuSceneLoader::loadSystems()
{
    auto spriteRenderSystem = ADD_SYSTEM(SpriteRenderSystem);
    spriteRenderSystem->setRenderer(m_scene->renderer());

    auto textRenderSystem = ADD_SYSTEM(TextRenderSystem);
    textRenderSystem->setRenderer(m_scene->renderer());

    auto mouseEventTriggerSystem = ADD_SYSTEM(MouseEventTriggerSystem);
    mouseEventTriggerSystem->setInput(m_scene->input());
}
