//
// app.hpp
// pong
//
// Created by Damien Bendejacq on 23/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __APP_H__
#define __APP_H__

#include "jackbengine.hpp"
#include "scene/menu/menuScene.hpp"
#include "scene/multi/multiScene.hpp"

using namespace Jackbengine;

class App : public Application
{
    DISALLOW_COPY_AND_MOVE(App)

public:
    explicit App(ApplicationConfig& config);
    ~App() override = default;

    void frame(float delta) final;

private:
    SceneManager<Scene> m_sceneManager;
};

#endif // __APP_H__
