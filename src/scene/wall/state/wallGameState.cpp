//
// wallGameState.cpp
// pong
//
// Created by Damien Bendejacq on 12/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "wallGameState.hpp"
#include "../wallConst.hpp"
#include "wallGameOverState.hpp"

WallGameState::WallGameState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : SceneState(stateMachine, scene),
      m_ball {sceneLoader.entity("ball")},
      m_score {sceneLoader.entity("score")},
      m_ballTransform {&getComponent<Transform>(m_ball)},
      m_ballBoxShape {&getComponent<BoxShape>(m_ball)},
      m_scoreValue {&getComponent<Numerical<int>>(m_score)},
      m_scoreText {&getComponent<Text>(m_score)},
      m_aabbCollisionSystem {getSystem<AABBCollisionSystem>()}
{ }

void WallGameState::enter()
{
    m_aabbCollisionSystem.setCallback(
        [scoreValue = m_scoreValue, scoreText = m_scoreText]
        (float delta, ComponentCollection& components1, ComponentCollection& components2, AABBCollisionSide collisionSide)
        {
            return onCollision(delta, components1, components2, collisionSide, scoreValue, scoreText);
        }
    );
}

void WallGameState::frame(float)
{
    if (m_ballTransform->positionX() + m_ballBoxShape->width() + WallConst::BallOutOfScreenShift < 0.0f)
    {
        stateMachine().goToState<WallGameOverState>();
    }
}

void WallGameState::exit()
{
    m_aabbCollisionSystem.unsetCallback();
}

bool WallGameState::onCollision(float, ComponentCollection& components1, ComponentCollection& components2,
                                AABBCollisionSide collisionSide, Numerical<int> *scoreValue, Text *scoreText)
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
        if (WallConst::BallSpeedMax > ballSpeedVal)
        {
            ballSpeed.increment(WallConst::BallSpeedIncr);
        }

        scoreValue->increment(1);
        scoreText->setText(std::to_string(scoreValue->get()));

        result = true;
    }

    if ("ball" == tag1.get())
    {
        auto& audioSource = components2.get<AudioSource>();
        audioSource.play();
    }

    return result;
}
