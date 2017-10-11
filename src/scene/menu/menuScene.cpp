//
// menuScene.cpp
// pong
//
// Created by Damien Bendejacq on 23/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "menuScene.hpp"
#include "../multi/multiScene.hpp"

IMPORT_TEXT_RESOURCE(menu_tmx)
IMPORT_BINARY_RESOURCE(default_font)
IMPORT_BINARY_RESOURCE(tileset_png)

MenuScene::MenuScene(Application& application, SceneManager<Scene>& sceneManager)
    : Scene(application, sceneManager)
{
    TmxSceneLoader sceneLoader {*this, menu_tmx, tileset_png, tileset_png_size, default_font, default_font_size};

    configure(sceneLoader);
}

void MenuScene::onPlayClick()
{
    loadScene<MultiScene>();
    cursor().setCursor(CursorType::Default);
}

void MenuScene::onQuitClick()
{
    exitApplication();
}

void MenuScene::configure(const TmxSceneLoader& sceneLoader)
{
    // Play button
    {
        loadButton(sceneLoader.entity("play"), [this]() { onPlayClick(); });
    }

    // Quit button
    {
        auto quit = sceneLoader.entity("quit");

#ifndef EMSCRIPTEN
        loadButton(quit, [this]() { onQuitClick(); });
#else
        disableEntity(quit);
#endif
    }
}

void MenuScene::loadButton(Entity entity, MouseCallback onLeftClick)
{
    addComponent<MouseListenerComponent>(entity);

    auto& textComponent = getComponent<Text>(entity);
    auto& mouseListener = getComponent<MouseListener>(entity);

    const auto onEnter = [this, &textComponent]()
    {
        textComponent.setForeground(Color32(221, 173, 29));
        cursor().setCursor(CursorType::Hand);
    };
    const auto onExit = [this, &textComponent]()
    {
        textComponent.setForeground(Color32(255, 255, 255));
        cursor().setCursor(CursorType::Default);
    };

    mouseListener.onEnter(onEnter);
    mouseListener.onExit(onExit);
    mouseListener.onLeftClick(std::move(onLeftClick));
}
