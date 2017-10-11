//
// serviceState.cpp
// pong
//
// Created by Damien Bendejacq on 27/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "serviceState.hpp"
#include "gameState.hpp"

ServiceState::ServiceState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : State(stateMachine),
      m_scene {scene},
      m_leftPaddle {sceneLoader.entity("left_paddle")},
      m_rightPaddle {sceneLoader.entity("right_paddle")},
      m_ball {sceneLoader.entity("ball")},
      m_goal1 {sceneLoader.entity("goal_1")},
      m_goal2 {sceneLoader.entity("goal_2")},
      m_leftPaddleInstruction1 {sceneLoader.entity("left_paddle_instruction_1")},
      m_leftPaddleInstruction2 {sceneLoader.entity("left_paddle_instruction_2")},
      m_rightPaddleInstruction1 {sceneLoader.entity("right_paddle_instruction_1")},
      m_rightPaddleInstruction2 {sceneLoader.entity("right_paddle_instruction_2")},
      m_ballInstruction1 {sceneLoader.entity("launch_ball_instruction_1")},
      m_ballInstruction2 {sceneLoader.entity("launch_ball_instruction_2")}
{
    m_leftPaddleIsServing = &m_scene.getComponent<Numerical<bool>>(m_leftPaddle);
    m_rightPaddleIsServing = &m_scene.getComponent<Numerical<bool>>(m_rightPaddle);
    m_ballBoxShape = &m_scene.getComponent<BoxShape>(m_ball);
    m_ballVelocity = &m_scene.getComponent<Velocity>(m_ball);
    m_ballSpeed = &m_scene.getComponent<Numerical<int>>(m_ball);
    m_ballTransform = &m_scene.getComponent<Transform>(m_ball);
    m_ballTransform->setPosition(-32.0f, -32.0f);

    if (0 == (std::rand() % 2)) // NOLINT
    {
        m_leftPaddleIsServing->set(true);
        m_rightPaddleIsServing->set(false);
    }
    else
    {
        m_rightPaddleIsServing->set(true);
        m_leftPaddleIsServing->set(false);
    }

    showInstructions(true);
}

void ServiceState::enter()
{
    if (m_leftPaddleIsServing->get())
    {
        m_servingPaddle = m_leftPaddle;
    }
    else
    {
        m_servingPaddle = m_rightPaddle;
    }
    m_servingPaddleTransform = &m_scene.getComponent<Transform>(m_servingPaddle);
    m_servingPaddleBoxShape = &m_scene.getComponent<BoxShape>(m_servingPaddle);

    m_scene.disableComponent<Velocity>(m_ball);
}

void ServiceState::frame(float)
{
    stickBallToPaddle();

    if (m_scene.input().keyPress(KeyboardKey::Space))
    {
        launchBall();

        stateMachine().goToState<GameState>();
    }
}

void ServiceState::exit()
{
    showInstructions(false);
}

void ServiceState::stickBallToPaddle()
{
    Vec2f ballPos;
    if (m_servingPaddle == m_leftPaddle)
    {
        ballPos.x = m_servingPaddleTransform->positionX() + m_servingPaddleBoxShape->width() + 2.0f;
    }
    else
    {
        ballPos.x = m_servingPaddleTransform->positionX() - m_ballBoxShape->width() - 2.0f;
    }
    ballPos.y = m_servingPaddleTransform->positionY()
                + m_servingPaddleBoxShape->height() * 0.5f
                - m_ballBoxShape->height() * 0.5f;

    m_ballTransform->setPosition(ballPos.x, ballPos.y);
}

void ServiceState::launchBall()
{
    Vec2f ballVel;
    ballVel.x = m_servingPaddle == m_leftPaddle ? 1.0f : -1.0f;
    ballVel.y = 0 == std::rand() % 2 ? -1.0f : 1.0f; // NOLINT
    ballVel.normalize();

    auto ballSpeed = m_ballSpeed->get();
    m_ballVelocity->set(ballVel.x * ballSpeed, ballVel.y * ballSpeed);
    m_scene.enableComponent<Velocity>(m_ball);
}

void ServiceState::showInstructions(bool show)
{
    m_scene.enableEntity(m_goal1, show);
    m_scene.enableEntity(m_goal2, show);
    m_scene.enableEntity(m_leftPaddleInstruction1, show);
    m_scene.enableEntity(m_leftPaddleInstruction2, show);
    m_scene.enableEntity(m_rightPaddleInstruction1, show);
    m_scene.enableEntity(m_rightPaddleInstruction2, show);
    m_scene.enableEntity(m_ballInstruction1, show);
    m_scene.enableEntity(m_ballInstruction2, show);
}
