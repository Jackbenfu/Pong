//
// gameState.cpp
// pong
//
// Created by Damien Bendejacq on 27/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "gameState.hpp"
#include "serviceState.hpp"
#include "gameOverState.hpp"
#include "../const/multiConst.hpp"

GameState::GameState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : State(stateMachine),
      m_scene {scene},
      m_leftPaddle {sceneLoader.entity("left_paddle")},
      m_rightPaddle {sceneLoader.entity("right_paddle")},
      m_ball {sceneLoader.entity("ball")},
      m_leftScore {sceneLoader.entity("left_score")},
      m_rightScore {sceneLoader.entity("right_score")}
{
    auto& aabbCollisionSystem = m_scene.getSystem<AABBCollisionSystem>();
    aabbCollisionSystem.setCallback(onCollision);

    m_ballTransform = &m_scene.getComponent<Transform>(m_ball);
    m_ballBoxShape = &m_scene.getComponent<BoxShape>(m_ball);
    m_leftScoreValue = &m_scene.getComponent<Numerical<int>>(m_leftScore);
    m_leftScoreText = &m_scene.getComponent<Text>(m_leftScore);
    m_rightScoreValue = &m_scene.getComponent<Numerical<int>>(m_rightScore);
    m_rightScoreText = &m_scene.getComponent<Text>(m_rightScore);
    m_leftPaddleIsServing = &m_scene.getComponent<Numerical<bool>>(m_leftPaddle);
    m_rightPaddleIsServing = &m_scene.getComponent<Numerical<bool>>(m_rightPaddle);
}

void GameState::frame(float)
{
    auto leftScore = m_leftScoreValue->get();
    auto rightScore = m_rightScoreValue->get();

    auto needToRestartGame = false;
    if (m_ballTransform->positionX() > m_scene.renderer().width())
    {
        needToRestartGame = true;
        m_leftPaddleIsServing->set(true);
        m_rightPaddleIsServing->set(false);
        updateScore(m_leftScore, ++leftScore);
    }
    else if (m_ballTransform->positionX() + m_ballBoxShape->width() < 0.0f)
    {
        needToRestartGame = true;
        m_rightPaddleIsServing->set(true);
        m_leftPaddleIsServing->set(false);
        updateScore(m_rightScore, ++rightScore);
    }

    if (MultiConst::ScoreToWin == leftScore || MultiConst::ScoreToWin == rightScore)
    {
        stateMachine().goToState<GameOverState>();
    }
    else if (needToRestartGame)
    {
        stateMachine().goToState<ServiceState>();
    }
}

bool GameState::onCollision(float, ComponentCollection& components1,
                            ComponentCollection& components2, AABBCollisionSide collisionSide)
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
        if (MultiConst::BallSpeedMax > ballSpeedVal)
        {
            ballSpeed.increment(MultiConst::BallSpeedIncr);
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

void GameState::updateScore(Entity scoreEntity, int newScore)
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
