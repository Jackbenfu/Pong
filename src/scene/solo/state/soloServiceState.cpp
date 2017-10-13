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
    : State(stateMachine),
      m_scene {scene},
      m_ball {sceneLoader.entity("ball")},
      m_instruction1 {sceneLoader.entity("instruction_1")},
      m_instruction2 {sceneLoader.entity("instruction_2")},
      m_instruction3 {sceneLoader.entity("instruction_3")},
      m_instruction4 {sceneLoader.entity("instruction_4")},
      m_instruction5 {sceneLoader.entity("instruction_5")},
      m_instruction6 {sceneLoader.entity("instruction_6")},
      m_ballVelocity {&m_scene.getComponent<Velocity>(m_ball)},
      m_ballSpeed {&m_scene.getComponent<Numerical<int>>(m_ball)}
{ }

void SoloServiceState::frame(float)
{
    if (m_scene.input().keyPress(KeyboardKey::Space))
    {
        launchBall();
        hideInstructions();

        stateMachine().goToState<SoloGameState>();
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
    m_scene.enableComponent<Velocity>(m_ball);
}

void SoloServiceState::hideInstructions()
{
    m_scene.disableEntity(m_instruction1);
    m_scene.disableEntity(m_instruction2);
    m_scene.disableEntity(m_instruction3);
    m_scene.disableEntity(m_instruction4);
    m_scene.disableEntity(m_instruction5);
    m_scene.disableEntity(m_instruction6);
}
