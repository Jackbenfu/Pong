//
//  gameScene.h
//  Pong
//
//  Created by Damien Bendejacq on 29/07/2015.
//  Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "jackbengine.h"
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

class GameScene : public TypedScene<GameScene>
{
public:
    GameScene();
    ~GameScene() override;

private:
    void frame(float delta) override;
    const char* name() override;
    bool initContents() override;

    GameSceneLoader *m_sceneLoader {nullptr};

    // AABB collision callback
    static bool onCollision(float delta, Entity *e1, Entity *e2, AABBCollisionSide collisionSide);

    // States
    PongState m_state = PongState::Service;
    void handleStateService();
    void handleStateRally();
    void handleStateGameOver();
    void handlePaddleMotion(Entity *paddle, KeyboardKey upKey, KeyboardKey downKey);
    void hideInstructions();

    void stickBallToRacket(Entity *paddle, bool sticked);
    void start();
    void updateScore(Entity *scoreEntity, uint newScore);

    int m_maxScore {0};

    Entity *m_leftPaddle {nullptr};
    Entity *m_rightPaddle {nullptr};
    Entity *m_ball {nullptr};
    Entity *m_leftScore {nullptr};
    Entity *m_rightScore {nullptr};
    Entity *m_gameOver {nullptr};
    Entity *m_leftResult {nullptr};
    Entity *m_rightResult {nullptr};
    Entity *m_servingPaddle {nullptr};
    Entity *m_goal1 {nullptr};
    Entity *m_goal2 {nullptr};
    Entity *m_leftPaddleInstruction1 {nullptr};
    Entity *m_leftPaddleInstruction2 {nullptr};
    Entity *m_rightPaddleInstruction1 {nullptr};
    Entity *m_rightPaddleInstruction2 {nullptr};
    Entity *m_launchBallInstruction1 {nullptr};
    Entity *m_launchBallInstruction2 {nullptr};
    Entity *m_terminateGameInstruction {nullptr};
};

#endif // __GAME_SCENE_H__
