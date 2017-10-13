//
// multiScene.hpp
// pong
//
// Created by Damien Bendejacq on 13/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __MULTI_SCENE_H__
#define __MULTI_SCENE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class MultiScene : public Scene
{
    DISALLOW_COPY_AND_MOVE(MultiScene)

public:
    MultiScene(Application& application, SceneManager<Scene>& sceneManager);
    ~MultiScene() override = default;

private:
    void frame(float delta) final;

    void handlePaddleMotion(Velocity *velocity, KeyboardKey upKey, KeyboardKey downKey);
    void configure(const TmxSceneLoader& sceneLoader);

    StateMachine m_stateMachine;

    Velocity *m_leftPaddleVelocity;
    Velocity *m_rightPaddleVelocity;
};

#endif // __MULTI_SCENE_H__
