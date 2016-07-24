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
    DELETE_SAFE(m_tmxLevel);
}

void PongMenu::frame(float delta)
{
    UNUSED(delta)

    // Nothing to do each frame!
}

const char* PongMenu::name()
{
    return "menu";
}

void PongMenu::onPlayClick(void *data)
{
    UNUSED(data)

    loadScene("game");
    cursor()->setCursor(CursorType::Default);
}

void PongMenu::onQuitClick(void *data)
{
    UNUSED(data)

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
    m_tmxLevel = new TmxMap();
    if (!m_tmxLevel->loadFromMemory(menu_768x576_tmx))
    {
        return false;
    }

    {
        /**
         * Background
         */
        m_background = ADD_ENTITY("background");

        ADD_COMPONENT(m_background, TransformComponent);
        ADD_COMPONENT(m_background, SpriteComponent)->loadFromLayer(
            renderer(),
            m_tmxLevel,
            "background",
            tileset_png,
            tileset_png_size
        );
    }

    {
        /**
         * Title
         */
        auto object = m_tmxLevel->getObjectGroup("menu")->getObject("title");

        m_title = ADD_ENTITY("title");

        ADD_COMPONENT(m_title, ContainerComponent)->setRect(
            object->getX(),
            object->getY(),
            object->getWidth(),
            object->getHeight()
        );

        auto text = ADD_COMPONENT(m_title, TextComponent);
        text->setText("PONG");
        text->setLayout(TextLayout::CenterCenter);
        text->setForeground(Color_White);
        text->setFontFromMemory(
            renderer(),
            default_font,
            default_font_size,
            144
        );
    }

    {
        /**
         * Play button
         */
        auto object = m_tmxLevel->getObjectGroup("menu")->getObject("play");

        m_play = ADD_ENTITY("play");

        ADD_COMPONENT(m_play, ContainerComponent)->setRect(
            object->getX(),
            object->getY(),
            object->getWidth(),
            object->getHeight()
        );

        auto text = ADD_COMPONENT(m_play, TextComponent);
        text->setText("Play");
        text->setLayout(TextLayout::CenterCenter);
        text->setForeground(Color_White);
        text->setFontFromMemory(
            renderer(),
            default_font,
            default_font_size,
            45
        );

        auto mouseListener = ADD_COMPONENT(m_play, MouseListenerComponent);
        mouseListener->onLeftClick(onPlayClick);
        mouseListener->onEnter(onButtonEnter, m_play);
        mouseListener->onExit(onButtonExit, m_play);
    }

#ifndef EMSCRIPTEN
    {
        /**
         * Quit button
         */
        auto object = m_tmxLevel->getObjectGroup("menu")->getObject("quit");

        m_quit = ADD_ENTITY("quit");

        ADD_COMPONENT(m_quit, ContainerComponent)->setRect(
            object->getX(),
            object->getY(),
            object->getWidth(),
            object->getHeight()
        );

        auto text = ADD_COMPONENT(m_quit, TextComponent);
        text->setText("Quit");
        text->setLayout(TextLayout::CenterCenter);
        text->setForeground(Color_White);
        text->setFontFromMemory(
            renderer(),
            default_font,
            default_font_size,
            45
        );

        auto mouseListener = ADD_COMPONENT(m_quit, MouseListenerComponent);
        mouseListener->onLeftClick(onQuitClick);
        mouseListener->onEnter(onButtonEnter, m_quit);
        mouseListener->onExit(onButtonExit, m_quit);
    }
#endif

    {
        /**
         * Author
         */
        auto object = m_tmxLevel->getObjectGroup("about")->getObject("author");

        m_author = ADD_ENTITY("author");

        ADD_COMPONENT(m_author, ContainerComponent)->setRect(
            object->getX(),
            object->getY(),
            object->getWidth(),
            object->getHeight()
        );

        auto text = ADD_COMPONENT(m_author, TextComponent);
        text->setText("Copyright (c) 2016 Jackben");
        text->setLayout(TextLayout::RightBottom);
        text->setForeground(Color_White);
        text->setFontFromMemory(
            renderer(),
            default_font,
            default_font_size,
            18
        );
    }

    {
        /**
         * Systems
         */
        m_spriteRenderSystem = ADD_SYSTEM(SpriteRenderSystem);
        m_spriteRenderSystem->setRenderer(renderer());

        m_textRenderSystem = ADD_SYSTEM(TextRenderSystem);
        m_textRenderSystem->setRenderer(renderer());

        m_mouseEventTriggerSystem = ADD_SYSTEM(MouseEventTriggerSystem);
        m_mouseEventTriggerSystem->setInput(input());

        m_debugProfileSystem = ADD_SYSTEM(DebugProfileSystem);
        m_debugProfileSystem->setRenderer(renderer());
        m_debugProfileSystem->setTimer(timer());
    }

    return true;
}
