//
// soloGameState.hpp
// pong
//
// Created by Damien Bendejacq on 12/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SOLO_GAME_STATE_H__
#define __SOLO_GAME_STATE_H__

#include "jackbengine.hpp"

using namespace Jackbengine;

class SoloGameState : public State
{
    DISALLOW_COPY_AND_MOVE(SoloGameState)

public:
    SoloGameState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader);
    ~SoloGameState() override = default;

    void frame(float delta) final;

private:
    static bool onCollision(
        float delta,
        ComponentCollection& components1,
        ComponentCollection& components2,
        AABBCollisionSide collisionSide,
        Numerical<int> *scoreValue,
        Text *scoreText
    );

    Scene& m_scene;

    Entity m_ball;
    Entity m_score;

    Transform *m_ballTransform;
    BoxShape *m_ballBoxShape;

    Numerical<int> *m_scoreValue;
    Text *m_scoreText;
};

#endif // __SOLO_GAME_STATE_H__
