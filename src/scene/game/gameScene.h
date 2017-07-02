//
//  gameScene.h
//  Pong
//
//  Created by Damien Bendejacq on 29/07/2015.
//  Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "jackbengine.hpp"
#include "gameSceneLoader.h"

#define PADDLE_SPEED        500.0f

#define BALL_SPEED_MIN      500
#define BALL_SPEED_MAX      800
#define BALL_SPEED_INCR     5

enum class PongState
{
    Service,
    Rally,
    GameOver
};

class GameScene : public Jackbengine::Scene
{
public:
    GameScene();
    ~GameScene() override;

    const char* name() override;

private:
    void frame(float delta) override;
    bool initContents() override;

    GameSceneLoader *m_sceneLoader = nullptr;

    // AABB collision callback
    static bool onCollision(
        float delta,
        Jackbengine::Entity *e1,
        Jackbengine::Entity *e2,
        Jackbengine::AABBCollisionSide collisionSide
    );

    // States
    PongState m_state = PongState::Service;
    void handleStateService();
    void handleStateRally();
    void handleStateGameOver();
    void handlePaddleMotion(
        Jackbengine::Entity *paddle,
        Jackbengine::KeyboardKey upKey,
        Jackbengine::KeyboardKey downKey
    );
    void hideInstructions();

    void stickBallToRacket(Jackbengine::Entity *paddle, bool sticked);
    void start();
    void updateScore(Jackbengine::Entity *scoreEntity, uint newScore);

    int m_maxScore = 0;

    Jackbengine::Entity *m_leftPaddle = nullptr;
    Jackbengine::Entity *m_rightPaddle = nullptr;
    Jackbengine::Entity *m_ball = nullptr;
    Jackbengine::Entity *m_leftScore = nullptr;
    Jackbengine::Entity *m_rightScore = nullptr;
    Jackbengine::Entity *m_gameOver = nullptr;
    Jackbengine::Entity *m_leftResult = nullptr;
    Jackbengine::Entity *m_rightResult = nullptr;
    Jackbengine::Entity *m_servingPaddle = nullptr;
    Jackbengine::Entity *m_goal1 = nullptr;
    Jackbengine::Entity *m_goal2 = nullptr;
    Jackbengine::Entity *m_leftPaddleInstruction1 = nullptr;
    Jackbengine::Entity *m_leftPaddleInstruction2 = nullptr;
    Jackbengine::Entity *m_rightPaddleInstruction1 = nullptr;
    Jackbengine::Entity *m_rightPaddleInstruction2 = nullptr;
    Jackbengine::Entity *m_launchBallInstruction1 = nullptr;
    Jackbengine::Entity *m_launchBallInstruction2 = nullptr;
    Jackbengine::Entity *m_terminateGameInstruction = nullptr;
};

#endif // __GAME_SCENE_H__
