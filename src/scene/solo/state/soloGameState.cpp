//
// soloGameState.cpp
// pong
//
// Created by Damien Bendejacq on 12/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "soloGameState.hpp"
#include "soloServiceState.hpp"
#include "../soloConst.hpp"

SoloGameState::SoloGameState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : State(stateMachine),
      m_scene {scene},
      m_ball {sceneLoader.entity("ball")},
      m_score {sceneLoader.entity("score")}
{
    m_ballTransform = &m_scene.getComponent<Transform>(m_ball);
    m_ballBoxShape = &m_scene.getComponent<BoxShape>(m_ball);
    m_scoreValue = &m_scene.getComponent<Numerical<int>>(m_score);
    m_scoreText = &m_scene.getComponent<Text>(m_score);

    auto collisionLambda = [this, scoreValue = m_scoreValue, scoreText = m_scoreText]
        (float delta, ComponentCollection& components1, ComponentCollection& components2, AABBCollisionSide collisionSide)
        {
            return onCollision(delta, components1, components2, collisionSide, scoreValue, scoreText);
        };

    auto& aabbCollisionSystem = m_scene.getSystem<AABBCollisionSystem>();
    aabbCollisionSystem.setCallback(collisionLambda);
}

void SoloGameState::frame(float)
{
    if (m_ballTransform->positionX() + m_ballBoxShape->width() < 0.0f)
    {
        stateMachine().goToState<SoloServiceState>();
    }
}

bool SoloGameState::onCollision(float, ComponentCollection& components1, ComponentCollection& components2,
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
        if (SoloConst::BallSpeedMax > ballSpeedVal)
        {
            ballSpeed.increment(SoloConst::BallSpeedIncr);
        }

        scoreValue->increment(1);
        scoreText->setText(std::to_string(scoreValue->get()));

        result = true;
    }

    if ("wall" == tag2.get() || "paddle" == tag2.get())
    {
        auto& audioSource = components2.get<AudioSource>();
        audioSource.play();
    }

    return result;
}
