//
//  pongGame.h
//  Pong
//
//  Created by Damien Bendejacq on 29/07/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __PONG_GAME_H__
#define __PONG_GAME_H__

#include "jackbengine.h"

#define PADDLE_SPEED        700.0f

#define BALL_SPEED_MIN      500
#define BALL_SPEED_MAX      800
#define BALL_SPEED_INCR     5

#define BALL_VELX           1000.0f
#define BALL_VELY_MAX       750.0f
#define BALL_VELY_CORNER    1500.0f

#define MAX_POINT           9

enum class PongState
{
    Service,
    Rally,
    GameOver
};

class PongGame : public TypedScene<PongGame>
{
public:
    PongGame();
    ~PongGame();

private:
    void frame(float delta) override;
    const char* name() override;
    bool initContents() override;

    TmxMap *m_tmxLevel = nullptr;

    // Entities
    Entity *m_background = nullptr;
    Entity *m_topWall = nullptr;
    Entity *m_bottomWall = nullptr;
    Entity *m_leftPaddle = nullptr;
    Entity *m_rightPaddle = nullptr;
    Entity *m_ball = nullptr;
    Entity *m_leftScore = nullptr;
    Entity *m_rightScore = nullptr;
    Entity *m_gameOver = nullptr;
    Entity *m_leftResult = nullptr;
    Entity *m_rightResult = nullptr;
    Entity *m_servingPaddle = nullptr;

    // Systems
    MotionSystem *m_motionSystem = nullptr;
    AABBCollisionSystem *m_aabbCollisionSystem = nullptr;
    SpriteRenderSystem *m_spriteRenderSystem = nullptr;
    TextRenderSystem *m_textRenderSystem = nullptr;
    DebugProfileSystem *m_debugProfileSystem = nullptr;

    // AABB collision callback
    static bool onCollision(float delta, Entity *e1, Entity *e2, AABBCollisionSide collisionSide);

    // States
    PongState m_state = PongState::Service;
    void handleStateService();
    void handleStateRally();
    static void handleStateGameOver();
    static void handlePaddleMotion(Entity *paddle, KeyboardKey upKey, KeyboardKey downKey);

    void stickBallToRacket(Entity *paddle, bool sticked) const;
    void start();
    void updateScore(Entity *scoreEntity, uint newScore) const;

    // Level loading
    Entity* loadBackground(const char *name) const;
    Entity* loadWall(const char *name) const;
    Entity* loadPaddle(const char *name) const;
    Entity* loadBall(const char *name) const;
    Entity* loadScore(const char *name) const;
    Entity* loadGameOver(const char *name) const;
    Entity* loadResult(const char *name) const;
};

#endif // __PONG_GAME_H__
