//
// 2playersGameState.cpp
// pong
//
// Created by Damien Bendejacq on 27/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "2playersGameState.hpp"
#include "2playersServiceState.hpp"
#include "2playersGameOverState.hpp"
#include "../../const.hpp"

TwoPlayersGameState::TwoPlayersGameState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : SceneState(stateMachine, scene),
      m_leftPaddle {sceneLoader.entity("left_paddle")},
      m_rightPaddle {sceneLoader.entity("right_paddle")},
      m_ball {sceneLoader.entity("ball")},
      m_leftScore {sceneLoader.entity("left_score")},
      m_rightScore {sceneLoader.entity("right_score")},
      m_leftPaddleIsServing {&getComponent<Numerical<bool>>(m_leftPaddle)},
      m_rightPaddleIsServing {&getComponent<Numerical<bool>>(m_rightPaddle)},
      m_ballTransform {&getComponent<Transform>(m_ball)},
      m_ballBoxShape {&getComponent<BoxShape>(m_ball)},
      m_leftScoreValue {&getComponent<Numerical<int>>(m_leftScore)},
      m_leftScoreText {&getComponent<Text>(m_leftScore)},
      m_rightScoreValue {&getComponent<Numerical<int>>(m_rightScore)},
      m_rightScoreText {&getComponent<Text>(m_rightScore)},
      m_aabbCollisionSystem {getSystem<AABBCollisionSystem>()}
{ }

void TwoPlayersGameState::enter()
{
    m_aabbCollisionSystem.setCallback(onCollision);
}

void TwoPlayersGameState::frame(float)
{
    auto leftScore = m_leftScoreValue->get();
    auto rightScore = m_rightScoreValue->get();

    auto needToRestartGame = false;
    if (m_ballTransform->positionX() > renderer().width() + Const::BallOutOfScreenShift)
    {
        needToRestartGame = true;
        m_leftPaddleIsServing->set(true);
        m_rightPaddleIsServing->set(false);
        updateScore(m_leftScore, ++leftScore);
    }
    else if (m_ballTransform->positionX() + m_ballBoxShape->width() + Const::BallOutOfScreenShift < 0.0f)
    {
        needToRestartGame = true;
        m_rightPaddleIsServing->set(true);
        m_leftPaddleIsServing->set(false);
        updateScore(m_rightScore, ++rightScore);
    }

    if (Const::ScoreToWin == leftScore || Const::ScoreToWin == rightScore)
    {
        stateMachine().goToState<TwoPlayersGameOverState>();
    }
    else if (needToRestartGame)
    {
        stateMachine().goToState<TwoPlayersServiceState>();
    }
}

void TwoPlayersGameState::exit()
{
    m_aabbCollisionSystem.unsetCallback();
}

bool TwoPlayersGameState::onCollision(float, ComponentCollection& components1, ComponentCollection& components2,
                                      AABBCollisionSide collisionSide)
{
    auto result = false;

    auto& tag1 = components1.get<Tag>();
    auto& tag2 = components2.get<Tag>();

    if ("ball" == tag1.get() && "paddle" == tag2.get()
        && (AABBCollisionSide::Left == collisionSide || AABBCollisionSide::Right == collisionSide))
    {
        auto& ballTransform = components1.get<Transform>();
        auto& ballVelocity = components1.get<Velocity>();
        auto& ballBoxShape = components1.get<BoxShape>();
        auto& ballSpeed = components1.get<Numerical<int>>();
        auto& paddleTransform = components2.get<Transform>();
        auto& paddleBoxShape = components2.get<BoxShape>();

        auto ballCenterY = ballTransform.positionY() + ballBoxShape.height() / 2.0f;
        auto paddleCenterY = paddleTransform.positionY() + paddleBoxShape.height() / 2.0f;
        auto hitFactor = (ballCenterY - paddleCenterY) / paddleBoxShape.height();

        Vec2f newBallVel;
        newBallVel.x = ballVelocity.x() > 0.0f ? -1.0f : 1.0f;
        newBallVel.y = hitFactor * 2;
        newBallVel.normalize();

        auto ballSpeedVal = ballSpeed.get();
        ballVelocity.set(newBallVel.x * ballSpeedVal, newBallVel.y * ballSpeedVal);
        if (Const::BallSpeedMax > ballSpeedVal)
        {
            ballSpeed.increment(Const::BallSpeedIncr);
        }

        result = true;
    }

    if ("ball" == tag1.get())
    {
        auto& audioSource = components2.get<AudioSource>();
        audioSource.play();
    }

    return result;
}

void TwoPlayersGameState::updateScore(Entity scoreEntity, int newScore)
{
    if (scoreEntity == m_leftScore)
    {
        m_leftScoreValue->set(newScore);
        m_leftScoreText->setText(std::to_string(newScore));
    }
    else
    {
        m_rightScoreValue->set(newScore);
        m_rightScoreText->setText(std::to_string(newScore));
    }
}
