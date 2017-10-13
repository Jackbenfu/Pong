//
// soloServiceState.hpp
// pong
//
// Created by Damien Bendejacq on 11/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SOLO_SERVICE_STATE_H__
#define __SOLO_SERVICE_STATE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class SoloServiceState : public State
{
    DISALLOW_COPY_AND_MOVE(SoloServiceState)

public:
    SoloServiceState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~SoloServiceState() override = default;

    void frame(float delta) final;

private:
    void launchBall();
    void hideInstructions();

    Scene& m_scene;

    Entity m_ball;
    Entity m_instruction1;
    Entity m_instruction2;
    Entity m_instruction3;
    Entity m_instruction4;
    Entity m_instruction5;
    Entity m_instruction6;

    Velocity *m_ballVelocity;
    Numerical<int> *m_ballSpeed;


};

#endif // __SOLO_SERVICE_STATE_H__
