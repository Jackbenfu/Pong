//
// wallScene.hpp
// pong
//
// Created by Damien Bendejacq on 11/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __WALL_SCENE_H__
#define __WALL_SCENE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class WallScene : public Scene
{
    DISALLOW_COPY_AND_MOVE(WallScene)

public:
    WallScene(Application& application, SceneManager<Scene>& sceneManager);
    ~WallScene() override = default;

private:
    void frame(float delta) final;

    void handlePaddleMotion(KeyboardKey upKey, KeyboardKey downKey);
    void configure(const TmxSceneLoader& sceneLoader);

    StateMachine m_stateMachine;

    Velocity *m_paddleVelocity;
};

#endif // __WALL_SCENE_H__
