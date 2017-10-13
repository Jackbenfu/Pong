//
// soloScene.hpp
// pong
//
// Created by Damien Bendejacq on 11/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SOLO_SCENE_H__
#define __SOLO_SCENE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class SoloScene : public Scene
{
    DISALLOW_COPY_AND_MOVE(SoloScene)

public:
    SoloScene(Application& application, SceneManager<Scene>& sceneManager);
    ~SoloScene() override = default;

private:
    void frame(float delta) final;

    void handlePaddleMotion(KeyboardKey upKey, KeyboardKey downKey);
    void configure(const TmxSceneLoader& sceneLoader);

    StateMachine m_stateMachine;

    Velocity *m_paddleVelocity;
};

#endif // __SOLO_SCENE_H__
