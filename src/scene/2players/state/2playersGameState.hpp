//
// 2playersGameState.hpp
// pong
//
// Created by Damien Bendejacq on 27/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __2_PLAYERS_GAME_STATE_H__
#define __2_PLAYERS_GAME_STATE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class TwoPlayersGameState : public SceneState
{
    DISALLOW_COPY_AND_MOVE(TwoPlayersGameState)

public:
    TwoPlayersGameState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~TwoPlayersGameState() override = default;

    void enter() final;
    void frame(float delta) final;
    void exit() final;

private:
    static bool onCollision(
        float delta,
        ComponentCollection& components1,
        ComponentCollection& components2,
        AABBCollisionSide collisionSide
    );

    void updateScore(Entity scoreEntity, int newScore);

    const Entity m_leftPaddle;
    const Entity m_rightPaddle;
    const Entity m_ball;
    const Entity m_leftScore;
    const Entity m_rightScore;

    Numerical<bool> *m_leftPaddleIsServing;
    Numerical<bool> *m_rightPaddleIsServing;

    Transform *m_ballTransform;
    BoxShape *m_ballBoxShape;

    Numerical<int> *m_leftScoreValue;
    Text *m_leftScoreText;

    Numerical<int> *m_rightScoreValue;
    Text *m_rightScoreText;

    AABBCollisionSystem& m_aabbCollisionSystem;
};

#endif // __2_PLAYERS_GAME_STATE_H__
