//
//  gameScene.cpp
//  Pong
//
//  Created by Damien Bendejacq on 29/07/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#include "gameScene.h"

IMPORT_TEXT_RESOURCE(game_768x576_tmx)

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
    DELETE_SAFE(m_sceneLoader);
}

void GameScene::frame(float delta)
{
    UNUSED(delta);

    handlePaddleMotion(m_leftPaddle, KeyboardKey::E, KeyboardKey::C);
    handlePaddleMotion(m_rightPaddle, KeyboardKey::Up, KeyboardKey::Down);

    switch (m_state)
    {
        case PongState::Service:
            handleStateService();
            break;

        case PongState::Rally:
            handleStateRally();
            break;

        case PongState::GameOver:
            handleStateGameOver();
            break;
    }

    if (input()->keyPress(KeyboardKey::Escape))
    {
        loadScene("menu");
    }
}

const char* GameScene::name()
{
    return "game";
}

void GameScene::handleStateService()
{
    if (input()->keyPress(KeyboardKey::Space))
    {
        m_state = PongState::Rally;

        Vec2f ballVel;
        ballVel.x = m_servingPaddle == m_leftPaddle ? 1.0f : -1.0f;
        ballVel.y = 0 == rand() % 2 ? -1.0f : 1.0f;
        ballVel.normalize();

        auto ballVelocity = GET_COMPONENT(m_ball, VelocityComponent);
        auto ballSpeed = GET_COMPONENT(m_ball, UintComponent)->get();
        ballVelocity->set(ballVel.x * ballSpeed, ballVel.y * ballSpeed);
        ENABLE_COMPONENT(m_ball, VelocityComponent);

        hideInstructions();
    }
    else
    {
        stickBallToRacket(m_servingPaddle, true);
    }
}

void GameScene::handleStateRally()
{
    auto ballTransform = GET_COMPONENT(m_ball, TransformComponent);
    auto ballBoxShape = GET_COMPONENT(m_ball, BoxShapeComponent);

    auto leftScore = GET_COMPONENT(m_leftScore, UintComponent)->get();
    auto rightScore = GET_COMPONENT(m_rightScore, UintComponent)->get();

    auto needToRestartRally = false;
    if (ballTransform->getPositionX() > renderer()->getWidth())
    {
        needToRestartRally = true;
        m_servingPaddle = m_leftPaddle;
        updateScore(m_leftScore, ++leftScore);
    }
    else if (ballTransform->getPositionX() + ballBoxShape->getWidth() < 0.0f)
    {
        needToRestartRally = true;
        m_servingPaddle = m_rightPaddle;
        updateScore(m_rightScore, ++rightScore);
    }

    if (m_maxScore == leftScore || m_maxScore == rightScore)
    {
        m_state = PongState::GameOver;

        ENABLE_ENTITY(m_gameOver);
        ENABLE_ENTITY(m_leftResult);
        ENABLE_ENTITY(m_rightResult);
        ENABLE_ENTITY(m_terminateGameInstruction);

        auto green = Color(69, 183, 130);
        auto red = Color(196, 89, 73);

        auto leftResultComponent = GET_COMPONENT(m_leftResult, TextComponent);
        auto rightResultComponent = GET_COMPONENT(m_rightResult, TextComponent);
        if (m_maxScore == leftScore)
        {
            leftResultComponent->setText("WIN");
            leftResultComponent->setForeground(green);
            rightResultComponent->setText("LOSE");
            rightResultComponent->setForeground(red);
        }
        else
        {
            leftResultComponent->setText("LOSE");
            leftResultComponent->setForeground(red);
            rightResultComponent->setText("WIN");
            rightResultComponent->setForeground(green);
        }
    }
    else if (needToRestartRally)
    {
        m_state = PongState::Service;

        stickBallToRacket(m_servingPaddle, false);
    }
}

void GameScene::handleStateGameOver()
{
    if (input()->keyPress(KeyboardKey::Space))
    {
        loadScene("menu");
    }
}

void GameScene::handlePaddleMotion(Entity *paddle, KeyboardKey upKey, KeyboardKey downKey)
{
    auto velocity = GET_COMPONENT(paddle, VelocityComponent);

    auto up = input()->keyDown(upKey);
    auto down = input()->keyDown(downKey);

    if (up ^ down)
    {
        velocity->set(0.0f, up ? -PADDLE_SPEED : PADDLE_SPEED);
    }
    else
    {
        velocity->set(0.0f, 0.0f);
    }
}

void GameScene::hideInstructions() const
{
    DISABLE_ENTITY(m_goal1);
    DISABLE_ENTITY(m_goal2);
    DISABLE_ENTITY(m_leftPaddleInstruction1);
    DISABLE_ENTITY(m_leftPaddleInstruction2);
    DISABLE_ENTITY(m_rightPaddleInstruction1);
    DISABLE_ENTITY(m_rightPaddleInstruction2);
    DISABLE_ENTITY(m_launchBallInstruction1);
    DISABLE_ENTITY(m_launchBallInstruction2);
}

void GameScene::stickBallToRacket(Entity *paddle, bool sticked) const
{
    if (!sticked)
    {
        DISABLE_COMPONENT(m_ball, VelocityComponent);
    }

    auto paddleTransform = GET_COMPONENT(paddle, TransformComponent);
    auto paddleBoxShape = GET_COMPONENT(paddle, BoxShapeComponent);
    auto ballBoxShape = GET_COMPONENT(m_ball, BoxShapeComponent);

    Vec2f ballPos;
    if (m_servingPaddle == m_leftPaddle)
    {
        ballPos.x = paddleTransform->getPositionX() + paddleBoxShape->getWidth() + 2.0f;
    }
    else
    {
        ballPos.x = paddleTransform->getPositionX() - ballBoxShape->getWidth() - 2.0f;
    }
    ballPos.y = paddleTransform->getPositionY() +
        paddleBoxShape->getHeight() * 0.5f - ballBoxShape->getHeight() * 0.5f;

    auto ballTransform = GET_COMPONENT(m_ball, TransformComponent);
    ballTransform->setPosition(ballPos.x, ballPos.y);
}

void GameScene::start()
{
    m_state = PongState::Service;

    m_servingPaddle = 0 == (rand() % 2) ? m_leftPaddle : m_rightPaddle;

    auto screenHeight = static_cast<float>(renderer()->getHeight());

    GET_COMPONENT(m_leftPaddle, TransformComponent)->setPositionY(
        screenHeight * 0.5f - GET_COMPONENT(m_leftPaddle, BoxShapeComponent)->getHeight() * 0.5f);
    GET_COMPONENT(m_rightPaddle, TransformComponent)->setPositionY(
        screenHeight * 0.5f - GET_COMPONENT(m_rightPaddle, BoxShapeComponent)->getHeight() * 0.5f);

    updateScore(m_leftScore, 0);
    updateScore(m_rightScore, 0);

    ENABLE_ENTITY(m_leftScore);
    ENABLE_ENTITY(m_rightScore);

    DISABLE_ENTITY(m_gameOver);
    DISABLE_ENTITY(m_leftResult);
    DISABLE_ENTITY(m_rightResult);

    stickBallToRacket(m_servingPaddle, false);

    GET_COMPONENT(m_ball, UintComponent)->set(BALL_SPEED_MIN);

    cursor()->setCursor(CursorType::Default);
}

void GameScene::updateScore(Entity *scoreEntity, uint newScore) const
{
    GET_COMPONENT(scoreEntity, UintComponent)->set(newScore);

    auto text = GET_COMPONENT(scoreEntity, TextComponent);
    text->setText(to_string(static_cast<long long>(newScore)));
}

bool GameScene::onCollision(
    float delta, Entity *e1, Entity *e2, AABBCollisionSide collisionSide)
{
    UNUSED(delta);

    auto result = false;

    auto tag1 = e1->getComponent<TagComponent>();
    auto tag2 = e2->getComponent<TagComponent>();

    if (0 == strcmp("ball", tag1->getTag()) && 0 == strcmp("paddle", tag2->getTag()) &&
        (AABBCollisionSide::Left == collisionSide || AABBCollisionSide::Right == collisionSide))
    {
        auto ballTransform = e1->getComponent<TransformComponent>();
        auto ballVelocity = e1->getComponent<VelocityComponent>();
        auto ballBoxShape = e1->getComponent<BoxShapeComponent>();
        auto paddleTransform = e2->getComponent<TransformComponent>();
        auto paddleBoxShape = e2->getComponent<BoxShapeComponent>();

        auto ballCenterY = ballTransform->getPositionY() + ballBoxShape->getHeight() / 2.0f;
        auto paddleCenterY = paddleTransform->getPositionY() + paddleBoxShape->getHeight() / 2.0f;

        auto hitFactor = (ballCenterY - paddleCenterY) / paddleBoxShape->getHeight();

        Vec2f newBallVel;
        newBallVel.x = ballVelocity->getX() > 0.0f ? -1.0f : 1.0f;
        newBallVel.y = hitFactor * 2;
        newBallVel.normalize();

        auto ballSpeed = e1->getComponent<UintComponent>();
        auto ballSpeedVal = ballSpeed->get();
        ballVelocity->set(newBallVel.x * ballSpeedVal, newBallVel.y * ballSpeedVal);
        if (BALL_SPEED_MAX > ballSpeedVal)
        {
            ballSpeed->increment(BALL_SPEED_INCR);
        }

        result = true;
    }

    if (0 == strcmp("ball", tag1->getTag()))
    {
        auto collisionSound = e2->getComponent<AudioSourceComponent>();
        collisionSound->play();
    }

    return result;
}

bool GameScene::initContents()
{
    m_sceneLoader = new GameSceneLoader(this);
    if (!m_sceneLoader->loadFromMemory(game_768x576_tmx))
    {
        DELETE_SAFE(m_sceneLoader);
        LOG_ERROR("Could not load Game scene");

        return false;
    }

    auto aabbCollisionSystem = GET_SYSTEM(AABBCollisionSystem);
    aabbCollisionSystem->setCallback(onCollision);

    m_leftPaddle = GET_ENTITY("left_paddle");
    m_rightPaddle = GET_ENTITY("right_paddle");
    m_ball = GET_ENTITY("ball");
    m_leftScore = GET_ENTITY("left_score");
    m_rightScore = GET_ENTITY("right_score");
    m_gameOver = GET_ENTITY("game_over");
    m_leftResult = GET_ENTITY("left_result");
    m_rightResult = GET_ENTITY("right_result");
    m_goal1 = GET_ENTITY("goal_1");
    m_goal2 = GET_ENTITY("goal_2");
    m_leftPaddleInstruction1 = GET_ENTITY("left_paddle_instruction_1");
    m_leftPaddleInstruction2 = GET_ENTITY("left_paddle_instruction_2");
    m_rightPaddleInstruction1 = GET_ENTITY("right_paddle_instruction_1");
    m_rightPaddleInstruction2 = GET_ENTITY("right_paddle_instruction_2");
    m_launchBallInstruction1 = GET_ENTITY("launch_ball_instruction_1");
    m_launchBallInstruction2 = GET_ENTITY("launch_ball_instruction_2");
    m_terminateGameInstruction = GET_ENTITY("terminate_game_instruction");

    m_maxScore = m_sceneLoader->getMaxScore();

    start();

    return true;
}
