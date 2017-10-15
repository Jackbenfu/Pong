//
// soloServiceState.cpp
// pong
//
// Created by Damien Bendejacq on 11/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "soloServiceState.hpp"
#include "soloGameState.hpp"

SoloServiceState::SoloServiceState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : SceneState(stateMachine, scene),
      m_ball {sceneLoader.entity("ball")},
      m_instruction1 {sceneLoader.entity("instruction_1")},
      m_instruction2 {sceneLoader.entity("instruction_2")},
      m_instruction3 {sceneLoader.entity("instruction_3")},
      m_instruction4 {sceneLoader.entity("instruction_4")},
      m_instruction5 {sceneLoader.entity("instruction_5")},
      m_instruction6 {sceneLoader.entity("instruction_6")},
      m_ballVelocity {&getComponent<Velocity>(m_ball)},
      m_ballSpeed {&getComponent<Numerical<int>>(m_ball)}
{ }

void SoloServiceState::frame(float)
{
    if (input().keyPress(KeyboardKey::Space))
    {
        launchBall();
        hideInstructions();

        goToState<SoloGameState>();
    }
}

void SoloServiceState::launchBall()
{
    Vec2f ballVel;
    ballVel.x = 1.0f;
    ballVel.y = 0 == std::rand() % 2 ? -1.0f : 1.0f; // NOLINT
    ballVel.normalize();

    auto ballSpeed = m_ballSpeed->get();
    m_ballVelocity->set(ballVel.x * ballSpeed, ballVel.y * ballSpeed);
    enableComponent<Velocity>(m_ball);
}

void SoloServiceState::hideInstructions()
{
    disableEntity(m_instruction1);
    disableEntity(m_instruction2);
    disableEntity(m_instruction3);
    disableEntity(m_instruction4);
    disableEntity(m_instruction5);
    disableEntity(m_instruction6);
}
