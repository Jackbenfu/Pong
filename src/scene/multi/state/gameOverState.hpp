//
// gameOverState.hpp
// pong
//
// Created by Damien Bendejacq on 02/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __GAME_OVER_STATE_H__
#define __GAME_OVER_STATE_H__

#include "serviceState.hpp"

class GameOverState : public State
{
    DISALLOW_COPY_AND_MOVE(GameOverState)

public:
    explicit GameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~GameOverState() override = default;

    void enter() final;
    void frame(float delta) final;

private:
    Scene& m_scene;

    const Entity m_leftScore;
    const Entity m_rightScore;
    const Entity m_leftResult;
    const Entity m_rightResult;
    const Entity m_gameOver;
    const Entity m_terminateGameInstruction;
};

#endif // __GAME_OVER_STATE_H__
