//
// 2playersScene.hpp
// pong
//
// Created by Damien Bendejacq on 13/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __2_PLAYERS_SCENE_H__
#define __2_PLAYERS_SCENE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class TwoPlayersScene : public Scene
{
    DISALLOW_COPY_AND_MOVE(TwoPlayersScene)

public:
    TwoPlayersScene(Application& application, SceneManager<Scene>& sceneManager);
    ~TwoPlayersScene() override = default;

private:
    void frame(float delta) final;

    void handlePaddleMotion(Velocity *velocity, KeyboardKey upKey, KeyboardKey downKey);
    void configure(const TmxSceneLoader& sceneLoader);

    StateMachine m_stateMachine;

    Velocity *m_leftPaddleVelocity;
    Velocity *m_rightPaddleVelocity;
};

#endif // __2_PLAYERS_SCENE_H__
