//
// wallGameState.hpp
// pong
//
// Created by Damien Bendejacq on 12/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __WALL_GAME_STATE_H__
#define __WALL_GAME_STATE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class WallGameState : public SceneState
{
    DISALLOW_COPY_AND_MOVE(WallGameState)

public:
    WallGameState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~WallGameState() override = default;

    void enter() final;
    void frame(float delta) final;
    void exit() final;

private:
    static bool onCollision(
        float delta,
        ComponentCollection& components1,
        ComponentCollection& components2,
        AABBCollisionSide collisionSide,
        Numerical<int> *scoreValue,
        Text *scoreText
    );

    const Entity m_ball;
    const Entity m_score;

    Transform *m_ballTransform;
    BoxShape *m_ballBoxShape;

    Numerical<int> *m_scoreValue;
    Text *m_scoreText;

    AABBCollisionSystem& m_aabbCollisionSystem;
};

#endif // __WALL_GAME_STATE_H__
