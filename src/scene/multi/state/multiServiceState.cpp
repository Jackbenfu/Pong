//
// multiServiceState.cpp
// pong
//
// Created by Damien Bendejacq on 27/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "multiServiceState.hpp"
#include "multiGameState.hpp"

MultiServiceState::MultiServiceState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : SceneState(stateMachine, scene),
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
      m_ballInstruction2 {sceneLoader.entity("launch_ball_instruction_2")},
      m_leftPaddleIsServing {&getComponent<Numerical<bool>>(m_leftPaddle)},
      m_rightPaddleIsServing {&getComponent<Numerical<bool>>(m_rightPaddle)},
      m_ballTransform {&getComponent<Transform>(m_ball)},
      m_ballBoxShape {&getComponent<BoxShape>(m_ball)},
      m_ballVelocity {&getComponent<Velocity>(m_ball)},
      m_ballSpeed {&getComponent<Numerical<int>>(m_ball)}
{
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

void MultiServiceState::enter()
{
    if (m_leftPaddleIsServing->get())
    {
        m_servingPaddle = m_leftPaddle;
    }
    else
    {
        m_servingPaddle = m_rightPaddle;
    }
    m_servingPaddleTransform = &getComponent<Transform>(m_servingPaddle);
    m_servingPaddleBoxShape = &getComponent<BoxShape>(m_servingPaddle);

    disableComponent<Velocity>(m_ball);
}

void MultiServiceState::frame(float)
{
    stickBallToPaddle();

    if (input().keyPress(KeyboardKey::Space))
    {
        launchBall();

        stateMachine().goToState<MultiGameState>();
    }
}

void MultiServiceState::exit()
{
    showInstructions(false);
}

void MultiServiceState::stickBallToPaddle()
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

void MultiServiceState::launchBall()
{
    Vec2f ballVel;
    ballVel.x = m_servingPaddle == m_leftPaddle ? 1.0f : -1.0f;
    ballVel.y = 0 == std::rand() % 2 ? -1.0f : 1.0f; // NOLINT
    ballVel.normalize();

    auto ballSpeed = m_ballSpeed->get();
    m_ballVelocity->set(ballVel.x * ballSpeed, ballVel.y * ballSpeed);
    enableComponent<Velocity>(m_ball);
}

void MultiServiceState::showInstructions(bool show)
{
    enableEntity(m_goal1, show);
    enableEntity(m_goal2, show);
    enableEntity(m_leftPaddleInstruction1, show);
    enableEntity(m_leftPaddleInstruction2, show);
    enableEntity(m_rightPaddleInstruction1, show);
    enableEntity(m_rightPaddleInstruction2, show);
    enableEntity(m_ballInstruction1, show);
    enableEntity(m_ballInstruction2, show);
}
