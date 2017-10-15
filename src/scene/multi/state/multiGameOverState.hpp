//
// multiGameOverState.hpp
// pong
//
// Created by Damien Bendejacq on 02/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __MULTI_GAME_OVER_STATE_H__
#define __MULTI_GAME_OVER_STATE_H__

#include "multiServiceState.hpp"

class MultiGameOverState : public SceneState
{
    DISALLOW_COPY_AND_MOVE(MultiGameOverState)

public:
    MultiGameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~MultiGameOverState() override = default;

    void enter() final;
    void frame(float delta) final;

private:
    const Entity m_leftScore;
    const Entity m_rightScore;
    const Entity m_leftResult;
    const Entity m_rightResult;
    const Entity m_gameOver;
    const Entity m_terminateGameInstruction;
};

#endif // __MULTI_GAME_OVER_STATE_H__
