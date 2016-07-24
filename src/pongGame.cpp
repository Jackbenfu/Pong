//
//  pongGame.cpp
//  Pong
//
//  Created by Damien Bendejacq on 29/07/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#include "pongGame.h"

IMPORT_BINARY_RESOURCE(left_wav)
IMPORT_BINARY_RESOURCE(right_wav)
IMPORT_BINARY_RESOURCE(wall_wav)
IMPORT_BINARY_RESOURCE(default_font)
IMPORT_BINARY_RESOURCE(tileset_png)
IMPORT_TEXT_RESOURCE(game_768x576_tmx)

PongGame::PongGame()
{
}

PongGame::~PongGame()
{
    DELETE_SAFE(m_tmxLevel);
}

void PongGame::frame(float delta)
{
    UNUSED(delta)

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

const char* PongGame::name()
{
    return "game";
}

void PongGame::handleStateService()
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

void PongGame::handleStateRally()
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

    if (MAX_POINT == leftScore || MAX_POINT == rightScore)
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
        if (MAX_POINT == leftScore)
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

void PongGame::handleStateGameOver()
{
    if (input()->keyPress(KeyboardKey::Space))
    {
        loadScene("menu");
    }
}

void PongGame::handlePaddleMotion(Entity *paddle, KeyboardKey upKey, KeyboardKey downKey)
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

void PongGame::hideInstructions() const
{
    DISABLE_ENTITY(m_leftPaddleInstruction1);
    DISABLE_ENTITY(m_leftPaddleInstruction2);
    DISABLE_ENTITY(m_rightPaddleInstruction1);
    DISABLE_ENTITY(m_rightPaddleInstruction2);
    DISABLE_ENTITY(m_launchBallInstruction1);
    DISABLE_ENTITY(m_launchBallInstruction2);
}

void PongGame::stickBallToRacket(Entity *paddle, bool sticked) const
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

void PongGame::start()
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

void PongGame::updateScore(Entity *scoreEntity, uint newScore) const
{
    GET_COMPONENT(scoreEntity, UintComponent)->set(newScore);

    auto text = GET_COMPONENT(scoreEntity, TextComponent);
    text->setText(to_string(static_cast<long long>(newScore)));
}

bool PongGame::onCollision(float delta, Entity *e1, Entity *e2, AABBCollisionSide collisionSide)
{
    UNUSED(delta)

    auto result = false;

    auto tag1 = GET_COMPONENT(e1, TagComponent);
    auto tag2 = GET_COMPONENT(e2, TagComponent);

    if (0 == strcmp("ball", tag1->getTag()) && 0 == strcmp("paddle", tag2->getTag()) &&
        (AABBCollisionSide::Left == collisionSide || AABBCollisionSide::Right == collisionSide))
    {
        auto ballTransform = GET_COMPONENT(e1, TransformComponent);
        auto ballVelocity = GET_COMPONENT(e1, VelocityComponent);
        auto ballBoxShape = GET_COMPONENT(e1, BoxShapeComponent);
        auto paddleTransform = GET_COMPONENT(e2, TransformComponent);
        auto paddleBoxShape = GET_COMPONENT(e2, BoxShapeComponent);

        auto ballCenterY = ballTransform->getPositionY() + ballBoxShape->getHeight() / 2.0f;
        auto paddleY = paddleTransform->getPositionY();
        auto paddleHeight = paddleBoxShape->getHeight();

        Vec2f newBallVel;

        if (ballCenterY < paddleY)
        {
            // Collision almost on top corner!
            newBallVel.y = -BALL_VELY_CORNER;
        }
        else if (ballCenterY > paddleY + paddleHeight)
        {
            // Collision almost on bottom corner!
            newBallVel.y = BALL_VELY_CORNER;
        }
        else
        {
            // Computing y velocity according to the position the ball hit the paddle
            auto percent = (ballCenterY - paddleY) * 100.0f / paddleHeight;
            auto maxVelY = BALL_VELY_MAX;
            newBallVel.y = percent * maxVelY / 100.0f;
            if (newBallVel.y < maxVelY / 2.0f)
            {
                newBallVel.y = newBallVel.y - maxVelY;
            }
        }

        newBallVel.x = 0.0f < ballVelocity->getX() ? -BALL_VELX : BALL_VELX;
        newBallVel.normalize();

        auto ballSpeed = GET_COMPONENT(e1, UintComponent);
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
        auto collisionSound = GET_COMPONENT(e2, AudioSourceComponent);
        collisionSound->play();
    }

    return result;
}

bool PongGame::initContents()
{
    m_tmxLevel = new TmxMap();
    if (!m_tmxLevel->loadFromMemory(game_768x576_tmx))
    {
        return false;
    }

    /**
     * Entities
     */
    m_background = loadBackground("background");
    m_topWall = loadWall("top_wall");
    m_bottomWall = loadWall("bottom_wall");
    m_leftPaddle = loadPaddle("left_paddle", left_wav, left_wav_size);
    m_rightPaddle = loadPaddle("right_paddle", right_wav, right_wav_size);
    m_ball = loadBall("ball");
    m_leftScore = loadScore("left_score");
    m_rightScore = loadScore("right_score");
    m_gameOver = loadGameOver("game_over");
    m_leftResult = loadResult("left_result");
    m_rightResult = loadResult("right_result");
    m_leftPaddleInstruction1 = loadInstruction("instructions", "left_paddle_instruction_1", "E or C:", TextLayout::RightCenter);
    m_leftPaddleInstruction2 = loadInstruction("instructions", "left_paddle_instruction_2", "move left paddle", TextLayout::LeftCenter);
    m_rightPaddleInstruction1 = loadInstruction("instructions", "right_paddle_instruction_1", "UP or DOWN:", TextLayout::RightCenter);
    m_rightPaddleInstruction2 = loadInstruction("instructions", "right_paddle_instruction_2", "move right paddle", TextLayout::LeftCenter);
    m_launchBallInstruction1 = loadInstruction("instructions", "launch_ball_instruction_1", "SPACEBAR:", TextLayout::RightCenter);
    m_launchBallInstruction2 = loadInstruction("instructions", "launch_ball_instruction_2", "launch the ball", TextLayout::LeftCenter);
    m_terminateGameInstruction = loadInstruction("scores", "terminate_game_instruction", "Press SPACEBAR...", TextLayout::CenterCenter);
    DISABLE_ENTITY(m_terminateGameInstruction);

    /**
     * Systems
     */
    m_motionSystem = ADD_SYSTEM(MotionSystem);

    m_aabbCollisionSystem = ADD_SYSTEM(AABBCollisionSystem);
    m_aabbCollisionSystem->addCollisionGroup("paddle", "wall");
    m_aabbCollisionSystem->addCollisionGroup("ball", "paddle");
    m_aabbCollisionSystem->addCollisionGroup("ball", "wall");
    m_aabbCollisionSystem->setCallback(onCollision);

    m_spriteRenderSystem = ADD_SYSTEM(SpriteRenderSystem);
    m_spriteRenderSystem->setRenderer(renderer());

    m_textRenderSystem = ADD_SYSTEM(TextRenderSystem);
    m_textRenderSystem->setRenderer(renderer());

    m_debugProfileSystem = ADD_SYSTEM(DebugProfileSystem);
    m_debugProfileSystem->setRenderer(renderer());
    m_debugProfileSystem->setTimer(timer());
    m_debugProfileSystem->setForeground(Color_Black);

    start();

    return true;
}

Entity* PongGame::loadBackground(const char *name) const
{
    auto entity = ADD_ENTITY(name);

    ADD_COMPONENT(entity, SpriteComponent)->loadFromLayer(
        renderer(),
        m_tmxLevel,
        name,
        tileset_png,
        tileset_png_size
    );
    ADD_COMPONENT(entity, TransformComponent);

    return entity;
}

Entity* PongGame::loadWall(const char *name) const
{
    auto objectGroup = m_tmxLevel->getObjectGroup(name);
    auto shape = objectGroup->getObject("shape");

    auto entity = ADD_ENTITY(name);

    ADD_COMPONENT(entity, TransformComponent)->setPosition(
        static_cast<float>(shape->getX()),
        static_cast<float>(shape->getY())
    );
    ADD_COMPONENT(entity, TagComponent)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    ADD_COMPONENT(entity, BoxShapeComponent)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    ADD_COMPONENT(entity, AudioSourceComponent)->loadFromMemory(
        wall_wav,
        wall_wav_size
    );
    ADD_COMPONENT(entity, VelocityComponent);

    return entity;
}

Entity* PongGame::loadPaddle(const char *name, const void *soundData, size_t soundDataSize) const
{
    auto objectGroup = m_tmxLevel->getObjectGroup(name);
    auto shape = objectGroup->getObject("shape");

    auto entity = addEntity(name);

    ADD_COMPONENT(entity, TransformComponent)->setPosition(
        static_cast<float>(shape->getX()),
        static_cast<float>(shape->getY())
    );
    ADD_COMPONENT(entity, TagComponent)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    ADD_COMPONENT(entity, BoxShapeComponent)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    ADD_COMPONENT(entity, AudioSourceComponent)->loadFromMemory(
        soundData,
        soundDataSize
    );
    ADD_COMPONENT(entity, SpriteComponent)->loadFromObjectGroup(
        renderer(),
        m_tmxLevel,
        name,
        tileset_png,
        tileset_png_size
    );
    ADD_COMPONENT(entity, VelocityComponent);

    return entity;
}

Entity* PongGame::loadBall(const char *name) const
{
    auto objectGroup = m_tmxLevel->getObjectGroup(name);
    auto shape = objectGroup->getObject("shape");

    auto entity = addEntity(name);

    ADD_COMPONENT(entity, TagComponent)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    ADD_COMPONENT(entity, BoxShapeComponent)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    ADD_COMPONENT(entity, SpriteComponent)->loadFromObjectGroup(
        renderer(),
        m_tmxLevel,
        name,
        tileset_png,
        tileset_png_size
    );
    ADD_COMPONENT(entity, UintComponent); // Stores ball's speed
    ADD_COMPONENT(entity, TransformComponent);
    ADD_COMPONENT(entity, VelocityComponent);

    return entity;
}

Entity* PongGame::loadScore(const char *name) const
{
    auto object = m_tmxLevel->getObjectGroup("scores")->getObject(name);

    auto entity = addEntity(name);

    ADD_COMPONENT(entity, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );
    ADD_COMPONENT(entity, TransformComponent);
    ADD_COMPONENT(entity, UintComponent); // Stores player's score

    auto text = ADD_COMPONENT(entity, TextComponent);
    text->setText("0");
    text->setLayout(TextLayout::CenterCenter);
    text->setFontFromMemory(
        renderer(),
        default_font,
        default_font_size,
        54
    );

    return entity;
}

Entity* PongGame::loadGameOver(const char *name) const
{
    auto object = m_tmxLevel->getObjectGroup("scores")->getObject(name);

    auto entity = addEntity(name);

    ADD_COMPONENT(entity, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = ADD_COMPONENT(entity, TextComponent);
    text->setText("GAME OVER");
    text->setLayout(TextLayout::CenterCenter);
    text->setFontFromMemory(
        renderer(),
        default_font,
        default_font_size,
        90
    );

    DISABLE_ENTITY(entity);

    return entity;
}

Entity* PongGame::loadResult(const char *name) const
{
    auto object = m_tmxLevel->getObjectGroup("scores")->getObject(name);

    auto entity = addEntity(name);

    ADD_COMPONENT(entity, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = ADD_COMPONENT(entity, TextComponent);
    text->setLayout(TextLayout::CenterCenter);
    text->setFontFromMemory(
        renderer(),
        default_font,
        default_font_size,
        63
    );

    return entity;
}

Entity* PongGame::loadInstruction(
    const char *group, const char *name, const char *text, TextLayout textLayout)
{
    auto object = m_tmxLevel->getObjectGroup(group)->getObject(name);

    auto entity = addEntity(name);

    ADD_COMPONENT(entity, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto textComponent = ADD_COMPONENT(entity, TextComponent);
    textComponent->setLayout(textLayout);
    textComponent->setText(text);
    textComponent->setForeground(Color_DarkGrey);
    textComponent->setFontFromMemory(
        renderer(),
        default_font,
        default_font_size,
        27
    );

    return entity;
}
