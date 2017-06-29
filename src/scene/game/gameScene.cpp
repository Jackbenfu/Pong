//
//  gameScene.cpp
//  Pong
//
//  Created by Damien Bendejacq on 29/07/2015.
//  Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#include <cstdlib>
#include "gameScene.h"

IMPORT_TEXT_RESOURCE(game_768x576_tmx)

GameScene::GameScene() = default;

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
        ballVel.y = 0 == std::rand() % 2 ? -1.0f : 1.0f;
        ballVel.normalize();

        auto ballVelocity = getComponent<VelocityComponent>(m_ball);
        auto ballSpeed = getComponent<UintComponent>(m_ball)->get();
        ballVelocity->set(ballVel.x * ballSpeed, ballVel.y * ballSpeed);
        enableComponent<VelocityComponent>(m_ball);

        hideInstructions();
    }
    else
    {
        stickBallToRacket(m_servingPaddle, true);
    }
}

void GameScene::handleStateRally()
{
    auto ballTransform = getComponent<TransformComponent>(m_ball);
    auto ballBoxShape = getComponent<BoxShapeComponent>(m_ball);

    auto leftScore = getComponent<UintComponent>(m_leftScore)->get();
    auto rightScore = getComponent<UintComponent>(m_rightScore)->get();

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

        enableEntity(m_gameOver);
        enableEntity(m_leftResult);
        enableEntity(m_rightResult);
        enableEntity(m_terminateGameInstruction);

        auto green = Color(69, 183, 130);
        auto red = Color(196, 89, 73);

        auto leftResultComponent = getComponent<TextComponent>(m_leftResult);
        auto rightResultComponent = getComponent<TextComponent>(m_rightResult);
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
    auto velocity = getComponent<VelocityComponent>(paddle);

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

void GameScene::hideInstructions()
{
    disableEntity(m_goal1);
    disableEntity(m_goal2);
    disableEntity(m_leftPaddleInstruction1);
    disableEntity(m_leftPaddleInstruction2);
    disableEntity(m_rightPaddleInstruction1);
    disableEntity(m_rightPaddleInstruction2);
    disableEntity(m_launchBallInstruction1);
    disableEntity(m_launchBallInstruction2);
}

void GameScene::stickBallToRacket(Entity *paddle, bool sticked)
{
    if (!sticked)
    {
        disableComponent<VelocityComponent>(m_ball);
    }

    auto paddleTransform = getComponent<TransformComponent>(paddle);
    auto paddleBoxShape = getComponent<BoxShapeComponent>(paddle);
    auto ballBoxShape = getComponent<BoxShapeComponent>(m_ball);

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

    auto ballTransform = getComponent<TransformComponent>(m_ball);
    ballTransform->setPosition(ballPos.x, ballPos.y);
}

void GameScene::start()
{
    m_state = PongState::Service;

    m_servingPaddle = 0 == (std::rand() % 2) ? m_leftPaddle : m_rightPaddle;

    auto screenHeight = static_cast<float>(renderer()->getHeight());

    getComponent<TransformComponent>(m_leftPaddle)->setPositionY(
        screenHeight * 0.5f - getComponent<BoxShapeComponent>(m_leftPaddle)->getHeight() * 0.5f);
    getComponent<TransformComponent>(m_rightPaddle)->setPositionY(
        screenHeight * 0.5f - getComponent<BoxShapeComponent>(m_rightPaddle)->getHeight() * 0.5f);

    updateScore(m_leftScore, 0);
    updateScore(m_rightScore, 0);

    enableEntity(m_leftScore);
    enableEntity(m_rightScore);

    disableEntity(m_gameOver);
    disableEntity(m_leftResult);
    disableEntity(m_rightResult);

    stickBallToRacket(m_servingPaddle, false);

    getComponent<UintComponent>(m_ball)->set(BALL_SPEED_MIN);

    cursor()->setCursor(CursorType::Default);
}

void GameScene::updateScore(Entity *scoreEntity, uint newScore)
{
    getComponent<UintComponent>(scoreEntity)->set(newScore);

    auto text = getComponent<TextComponent>(scoreEntity);
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

    auto aabbCollisionSystem = getSystem<AABBCollisionSystem>();
    aabbCollisionSystem->setCallback(onCollision);

    m_leftPaddle = getEntity("left_paddle");
    m_rightPaddle = getEntity("right_paddle");
    m_ball = getEntity("ball");
    m_leftScore = getEntity("left_score");
    m_rightScore = getEntity("right_score");
    m_gameOver = getEntity("game_over");
    m_leftResult = getEntity("left_result");
    m_rightResult = getEntity("right_result");
    m_goal1 = getEntity("goal_1");
    m_goal2 = getEntity("goal_2");
    m_leftPaddleInstruction1 = getEntity("left_paddle_instruction_1");
    m_leftPaddleInstruction2 = getEntity("left_paddle_instruction_2");
    m_rightPaddleInstruction1 = getEntity("right_paddle_instruction_1");
    m_rightPaddleInstruction2 = getEntity("right_paddle_instruction_2");
    m_launchBallInstruction1 = getEntity("launch_ball_instruction_1");
    m_launchBallInstruction2 = getEntity("launch_ball_instruction_2");
    m_terminateGameInstruction = getEntity("terminate_game_instruction");

    m_maxScore = m_sceneLoader->getMaxScore();

    start();

    return true;
}
