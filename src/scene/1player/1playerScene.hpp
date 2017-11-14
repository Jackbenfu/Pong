//
// 1playerScene.hpp
// pong
//
// Created by Damien Bendejacq on 10/11/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __1_PLAYER_SCENE_H__
#define __1_PLAYER_SCENE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class OnePlayerScene : public Scene
{
    DISALLOW_COPY_AND_MOVE(OnePlayerScene)

public:
    OnePlayerScene(Application& application, SceneManager<Scene>& sceneManager);
    ~OnePlayerScene() override = default;

private:
    void frame(float delta) final;

    void handlePaddleMotion(KeyboardKey upKey, KeyboardKey downKey);
    void configure(const TmxSceneLoader& sceneLoader);

    StateMachine m_stateMachine;

    Velocity *m_leftPaddleVelocity;
};

#endif // __1_PLAYER_SCENE_H__
