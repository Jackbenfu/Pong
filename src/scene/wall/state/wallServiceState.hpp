//
// wallServiceState.hpp
// pong
//
// Created by Damien Bendejacq on 11/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __WALL_SERVICE_STATE_H__
#define __WALL_SERVICE_STATE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class WallServiceState : public SceneState
{
    DISALLOW_COPY_AND_MOVE(WallServiceState)

public:
    WallServiceState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~WallServiceState() override = default;

    void frame(float delta) final;

private:
    void launchBall();
    void hideInstructions();

    const Entity m_ball;
    const Entity m_instruction1;
    const Entity m_instruction2;
    const Entity m_instruction3;
    const Entity m_instruction4;
    const Entity m_instruction5;
    const Entity m_instruction6;

    Velocity *m_ballVelocity;
    Numerical<int> *m_ballSpeed;
};

#endif // __WALL_SERVICE_STATE_H__
