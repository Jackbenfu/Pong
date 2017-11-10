//
// 2playersServiceState.hpp
// pong
//
// Created by Damien Bendejacq on 27/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __2_PLAYERS_SERVICE_STATE_H__
#define __2_PLAYERS_SERVICE_STATE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class TwoPlayersServiceState : public SceneState
{
    DISALLOW_COPY_AND_MOVE(TwoPlayersServiceState)

public:
    TwoPlayersServiceState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~TwoPlayersServiceState() override = default;

    void enter() final;
    void frame(float delta) final;
    void exit() final;

private:
    void stickBallToPaddle();
    void launchBall();
    void showInstructions(bool show);

    const Entity m_leftPaddle;
    const Entity m_rightPaddle;
    const Entity m_ball;
    const Entity m_goal1;
    const Entity m_goal2;
    const Entity m_leftPaddleInstruction1;
    const Entity m_leftPaddleInstruction2;
    const Entity m_rightPaddleInstruction1;
    const Entity m_rightPaddleInstruction2;
    const Entity m_ballInstruction1;
    const Entity m_ballInstruction2;

    Entity m_servingPaddle;

    Numerical<bool> *m_leftPaddleIsServing;
    Numerical<bool> *m_rightPaddleIsServing;

    Transform *m_servingPaddleTransform;
    BoxShape *m_servingPaddleBoxShape;

    Transform *m_ballTransform;
    BoxShape *m_ballBoxShape;
    Velocity *m_ballVelocity;
    Numerical<int> *m_ballSpeed;
};

#endif // __2_PLAYERS_SERVICE_STATE_H__
