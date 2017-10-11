//
// menuScene.hpp
// pong
//
// Created by Damien Bendejacq on 23/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class MenuScene : public Scene
{
    DISALLOW_COPY_AND_MOVE(MenuScene)

public:
    MenuScene(Application& application, SceneManager<Scene>& sceneManager);
    ~MenuScene() override = default;

private:
    void onPlayClick();
    void onQuitClick();

    void configure(const TmxSceneLoader& sceneLoader);
    void loadButton(Entity entity, MouseCallback onLeftClick);
};

#endif // __MENU_SCENE_H__
