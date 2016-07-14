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
    Entity *button = static_cast<Entity*>(data);

    TextComponent *text = getComponent<TextComponent>(button);
    if (text)
    {
        text->setForeground(Color_YellowGold);
    }

    cursor()->setCursor(CursorType::Hand);
}

void PongMenu::onButtonExit(void *data)
{
    Entity *button = static_cast<Entity*>(data);

    TextComponent *text = getComponent<TextComponent>(button);
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
        m_background = addEntity("background");

        addComponent<TransformComponent>(m_background);

        addComponent<SpriteComponent>(m_background)->loadFromLayer(
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

        m_title = addEntity("title");

        addComponent<ContainerComponent>(m_title)->setRect(
            object->getX(),
            object->getY(),
            object->getWidth(),
            object->getHeight()
        );

        addComponent<TextComponent>(m_title);
        getComponent<TextComponent>(m_title)->setText("PONG");
        getComponent<TextComponent>(m_title)->setLayout(TextLayout::CenterCenter);
        getComponent<TextComponent>(m_title)->setForeground(Color_White);
        getComponent<TextComponent>(m_title)->setFontFromMemory(
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

        m_play = addEntity("play");

        addComponent<ContainerComponent>(m_play)->setRect(
            object->getX(),
            object->getY(),
            object->getWidth(),
            object->getHeight()
        );

        addComponent<TextComponent>(m_play);
        getComponent<TextComponent>(m_play)->setText("Play");
        getComponent<TextComponent>(m_play)->setLayout(TextLayout::CenterCenter);
        getComponent<TextComponent>(m_play)->setForeground(Color_White);
        getComponent<TextComponent>(m_play)->setFontFromMemory(
            renderer(),
            default_font,
            default_font_size,
            45
        );

        addComponent<MouseListenerComponent>(m_play);
        getComponent<MouseListenerComponent>(m_play)->onLeftClick(onPlayClick);
        getComponent<MouseListenerComponent>(m_play)->onEnter(onButtonEnter, m_play);
        getComponent<MouseListenerComponent>(m_play)->onExit(onButtonExit, m_play);
    }

#ifndef EMSCRIPTEN
    {
        /**
         * Quit button
         */
        auto object = m_tmxLevel->getObjectGroup("menu")->getObject("quit");

        m_quit = addEntity("quit");

        addComponent<ContainerComponent>(m_quit)->setRect(
            object->getX(),
            object->getY(),
            object->getWidth(),
            object->getHeight()
        );

        addComponent<TextComponent>(m_quit);
        getComponent<TextComponent>(m_quit)->setText("Quit");
        getComponent<TextComponent>(m_quit)->setLayout(TextLayout::CenterCenter);
        getComponent<TextComponent>(m_quit)->setForeground(Color_White);
        getComponent<TextComponent>(m_quit)->setFontFromMemory(
            renderer(),
            default_font,
            default_font_size,
            45
        );

        addComponent<MouseListenerComponent>(m_quit);
        getComponent<MouseListenerComponent>(m_quit)->onLeftClick(onQuitClick);
        getComponent<MouseListenerComponent>(m_quit)->onEnter(onButtonEnter, m_quit);
        getComponent<MouseListenerComponent>(m_quit)->onExit(onButtonExit, m_quit);
    }
#endif

    {
        /**
         * Author
         */
        auto object = m_tmxLevel->getObjectGroup("about")->getObject("author");

        m_author = addEntity("author");

        addComponent<ContainerComponent>(m_author)->setRect(
            object->getX(),
            object->getY(),
            object->getWidth(),
            object->getHeight()
        );

        addComponent<TextComponent>(m_author);
        getComponent<TextComponent>(m_author)->setText("Copyright (c) 2016 Jackben");
        getComponent<TextComponent>(m_author)->setLayout(TextLayout::RightBottom);
        getComponent<TextComponent>(m_author)->setForeground(Color_White);
        getComponent<TextComponent>(m_author)->setFontFromMemory(
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
        m_spriteRenderSystem = addSystem<SpriteRenderSystem>();
        m_spriteRenderSystem->setRenderer(renderer());

        m_textRenderSystem = addSystem<TextRenderSystem>();
        m_textRenderSystem->setRenderer(renderer());

        m_mouseEventTriggerSystem = addSystem<MouseEventTriggerSystem>();
        m_mouseEventTriggerSystem->setInput(input());

        m_debugProfileSystem = addSystem<DebugProfileSystem>();
        m_debugProfileSystem->setRenderer(renderer());
        m_debugProfileSystem->setTimer(timer());
    }

    return true;
}
