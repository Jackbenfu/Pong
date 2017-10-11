//
// app.cpp
// pong
//
// Created by Damien Bendejacq on 23/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "app.hpp"

App::App(Jackbengine::ApplicationConfig& config)
    : Application(config)
{
    m_sceneManager.loadScene<MenuScene>(*this, m_sceneManager);
}

void App::frame(float delta)
{
    m_sceneManager.current().update(delta);
}
