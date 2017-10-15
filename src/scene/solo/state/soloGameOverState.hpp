//
// soloGameOverState.hpp
// pong
//
// Created by Damien Bendejacq on 15/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SOLO_GAME_OVER_STATE_H__
#define __SOLO_GAME_OVER_STATE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class SoloGameOverState : public SceneState
{
    DISALLOW_COPY_AND_MOVE(SoloGameOverState)

public:
    SoloGameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~SoloGameOverState() override = default;

    void enter() final;
    void frame(float delta) final;

private:
    const Entity m_gameOver;
    const Entity m_terminateGameInstruction;
};

#endif // __SOLO_GAME_OVER_STATE_H__
