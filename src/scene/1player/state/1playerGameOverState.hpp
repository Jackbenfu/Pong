//
// 1playerGameOverState.hpp
// pong
//
// Created by Damien Bendejacq on 02/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __1_PLAYER_GAME_OVER_STATE_H__
#define __1_PLAYER_GAME_OVER_STATE_H__

#include "1playerServiceState.hpp"

class OnePlayerGameOverState : public SceneState
{
    DISALLOW_COPY_AND_MOVE(OnePlayerGameOverState)

public:
    OnePlayerGameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~OnePlayerGameOverState() override = default;

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

#endif // __1_PLAYER_GAME_OVER_STATE_H__
