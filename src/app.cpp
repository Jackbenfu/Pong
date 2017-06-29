//
//  app.cpp
//  Pong
//
//  Created by Damien Bendejacq on 17/08/2015.
//  Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#include "app.h"
#include "scene/menu/menuScene.h"
#include "scene/game/gameScene.h"

App::App(bool fullscreen)
    : m_fullscreen(fullscreen)
{
}

App::~App() = default;

bool App::configure(ApplicationConfig& config)
{
    config.general_title = "Pong";
    config.render_width = 768;
    config.render_height = 576;
    config.render_fullscreen = m_fullscreen;

    addScene<MenuScene>();
    addScene<GameScene>();

    return true;
}
