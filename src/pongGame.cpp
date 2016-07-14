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

        VelocityComponent *ballVelocity = getComponent<VelocityComponent>(m_ball);
        uint ballSpeed = getComponent<UintComponent>(m_ball)->get();
        ballVelocity->set(ballVel.x * ballSpeed, ballVel.y * ballSpeed);
        enableComponent<VelocityComponent>(m_ball);

        hideInstructions();
    }
    else
    {
        stickBallToRacket(m_servingPaddle, true);
    }
}

void PongGame::handleStateRally()
{
    TransformComponent *ballTransform = getComponent<TransformComponent>(m_ball);
    BoxShapeComponent *ballBoxShape = getComponent<BoxShapeComponent>(m_ball);

    uint leftScore = getComponent<UintComponent>(m_leftScore)->get();
    uint rightScore = getComponent<UintComponent>(m_rightScore)->get();

    bool needToRestartRally = false;
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

        enableEntity(m_gameOver);
        enableEntity(m_leftResult);
        enableEntity(m_rightResult);

        const Color green = Color(69, 183, 130);
        const Color red = Color(196, 89, 73);

        TextComponent *leftResultComponent = getComponent<TextComponent>(m_leftResult);
        TextComponent *rightResultComponent = getComponent<TextComponent>(m_rightResult);
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
    VelocityComponent *velocity = getComponent<VelocityComponent>(paddle);

    bool up = input()->keyDown(upKey);
    bool down = input()->keyDown(downKey);

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
    disableEntity(m_leftPaddleInstruction);
    disableEntity(m_rightPaddleInstruction);
    disableEntity(m_launchBallInstruction);
}

void PongGame::stickBallToRacket(Entity *paddle, bool sticked) const
{
    if (!sticked)
    {
        disableComponent<VelocityComponent>(m_ball);
    }

    TransformComponent *paddleTransform = getComponent<TransformComponent>(paddle);
    BoxShapeComponent *paddleBoxShape = getComponent<BoxShapeComponent>(paddle);
    BoxShapeComponent *ballBoxShape = getComponent<BoxShapeComponent>(m_ball);

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

    TransformComponent *ballTransform = getComponent<TransformComponent>(m_ball);
    ballTransform->setPosition(ballPos.x, ballPos.y);
}

void PongGame::start()
{
    m_state = PongState::Service;

    m_servingPaddle = 0 == (rand() % 2) ? m_leftPaddle : m_rightPaddle;

    float screenHeight = static_cast<float>(renderer()->getHeight());

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

void PongGame::updateScore(Entity *scoreEntity, uint newScore) const
{
    getComponent<UintComponent>(scoreEntity)->set(newScore);

    TextComponent *text = getComponent<TextComponent>(scoreEntity);
    text->setText(to_string(static_cast<long long>(newScore)));
}

bool PongGame::onCollision(float delta, Entity *e1, Entity *e2, AABBCollisionSide collisionSide)
{
    UNUSED(delta)

    bool result = false;

    TagComponent *tag1 = getComponent<TagComponent>(e1);
    TagComponent *tag2 = getComponent<TagComponent>(e2);

    if (0 == strcmp("ball", tag1->getTag()) && 0 == strcmp("paddle", tag2->getTag()) &&
        (AABBCollisionSide::Left == collisionSide || AABBCollisionSide::Right == collisionSide))
    {
        TransformComponent *ballTransform = getComponent<TransformComponent>(e1);
        VelocityComponent *ballVelocity = getComponent<VelocityComponent>(e1);
        BoxShapeComponent *ballBoxShape = getComponent<BoxShapeComponent>(e1);
        TransformComponent *paddleTransform = getComponent<TransformComponent>(e2);
        BoxShapeComponent *paddleBoxShape = getComponent<BoxShapeComponent>(e2);

        float ballCenterY = ballTransform->getPositionY() + ballBoxShape->getHeight() / 2.0f;
        float paddleY = paddleTransform->getPositionY();
        float paddleHeight = paddleBoxShape->getHeight();

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
            float percent = (ballCenterY - paddleY) * 100.0f / paddleHeight;
            float maxVelY = BALL_VELY_MAX;
            newBallVel.y = percent * maxVelY / 100.0f;
            if (newBallVel.y < maxVelY / 2.0f)
            {
                newBallVel.y = newBallVel.y - maxVelY;
            }
        }

        newBallVel.x = 0.0f < ballVelocity->getX() ? -BALL_VELX : BALL_VELX;
        newBallVel.normalize();

        UintComponent *ballSpeed = getComponent<UintComponent>(e1);
        uint ballSpeedVal = ballSpeed->get();
        ballVelocity->set(newBallVel.x * ballSpeedVal, newBallVel.y * ballSpeedVal);

        if (BALL_SPEED_MAX > ballSpeedVal)
        {
            ballSpeed->increment(BALL_SPEED_INCR);
        }

        result = true;
    }

    if (0 == strcmp("ball", tag1->getTag()))
    {
        AudioSourceComponent *collisionSound = getComponent<AudioSourceComponent>(e2);
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
    m_leftPaddleInstruction = loadInstruction(
        "left_paddle_instruction", "                E or C:     move left paddle"
    );
    m_rightPaddleInstruction = loadInstruction(
        "right_paddle_instruction", "           UP or DOWN:     move right paddle"
    );
    m_launchBallInstruction = loadInstruction(
        "launch_ball_instruction", "             SPACEBAR:     launch the ball!"
    );

    /**
     * Systems
     */
    m_motionSystem = addSystem<MotionSystem>();

    m_aabbCollisionSystem = addSystem<AABBCollisionSystem>();
    m_aabbCollisionSystem->addCollisionGroup("paddle", "wall");
    m_aabbCollisionSystem->addCollisionGroup("ball", "paddle");
    m_aabbCollisionSystem->addCollisionGroup("ball", "wall");
    m_aabbCollisionSystem->setCallback(onCollision);

    m_spriteRenderSystem = addSystem<SpriteRenderSystem>();
    m_spriteRenderSystem->setRenderer(renderer());

    m_textRenderSystem = addSystem<TextRenderSystem>();
    m_textRenderSystem->setRenderer(renderer());

    m_debugProfileSystem = addSystem<DebugProfileSystem>();
    m_debugProfileSystem->setRenderer(renderer());
    m_debugProfileSystem->setTimer(timer());
    m_debugProfileSystem->setForeground(Color_Black);

    start();

    return true;
}

Entity* PongGame::loadBackground(const char *name) const
{
    auto entity = addEntity(name);

    addComponent<SpriteComponent>(entity)->loadFromLayer(
        renderer(),
        m_tmxLevel,
        name,
        tileset_png,
        tileset_png_size
    );
    addComponent<TransformComponent>(entity);

    return entity;
}

Entity* PongGame::loadWall(const char *name) const
{
    auto objectGroup = m_tmxLevel->getObjectGroup(name);
    auto shape = objectGroup->getObject("shape");
    auto entity = addEntity(name);

    addComponent<TransformComponent>(entity)->setPosition(
        static_cast<float>(shape->getX()),
        static_cast<float>(shape->getY())
    );
    addComponent<TagComponent>(entity)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    addComponent<BoxShapeComponent>(entity)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    addComponent<AudioSourceComponent>(entity)->loadFromMemory(
        wall_wav,
        wall_wav_size
    );
    addComponent<VelocityComponent>(entity);

    return entity;
}

Entity* PongGame::loadPaddle(const char *name, const void *soundData, size_t soundDataSize) const
{
    auto objectGroup = m_tmxLevel->getObjectGroup(name);
    auto shape = objectGroup->getObject("shape");
    auto entity = addEntity(name);

    addComponent<TransformComponent>(entity)->setPosition(
        static_cast<float>(shape->getX()),
        static_cast<float>(shape->getY())
    );
    addComponent<TagComponent>(entity)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    addComponent<BoxShapeComponent>(entity)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    addComponent<AudioSourceComponent>(entity)->loadFromMemory(
        soundData,
        soundDataSize
    );
    addComponent<SpriteComponent>(entity)->loadFromObjectGroup(
        renderer(),
        m_tmxLevel,
        name,
        tileset_png,
        tileset_png_size
    );
    addComponent<VelocityComponent>(entity);

    return entity;
}

Entity* PongGame::loadBall(const char *name) const
{
    auto objectGroup = m_tmxLevel->getObjectGroup(name);
    auto shape = objectGroup->getObject("shape");
    auto entity = addEntity(name);

    addComponent<TagComponent>(entity)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    addComponent<BoxShapeComponent>(entity)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    addComponent<SpriteComponent>(entity)->loadFromObjectGroup(
        renderer(),
        m_tmxLevel,
        name,
        tileset_png,
        tileset_png_size
    );
    addComponent<UintComponent>(entity); // Stores ball's speed
    addComponent<TransformComponent>(entity);
    addComponent<VelocityComponent>(entity);

    return entity;
}

Entity* PongGame::loadScore(const char *name) const
{
    auto object = m_tmxLevel->getObjectGroup("scores")->getObject(name);
    auto entity = addEntity(name);

    addComponent<ContainerComponent>(entity)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );
    addComponent<TransformComponent>(entity);
    addComponent<UintComponent>(entity); // Stores player's score

    addComponent<TextComponent>(entity);
    getComponent<TextComponent>(entity)->setText("0");
    getComponent<TextComponent>(entity)->setLayout(TextLayout::CenterCenter);
    getComponent<TextComponent>(entity)->setFontFromMemory(
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

    addComponent<ContainerComponent>(entity)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    addComponent<TextComponent>(entity);
    getComponent<TextComponent>(entity)->setText("GAME OVER");
    getComponent<TextComponent>(entity)->setLayout(TextLayout::CenterCenter);
    getComponent<TextComponent>(entity)->setFontFromMemory(
        renderer(),
        default_font,
        default_font_size,
        90
    );

    disableEntity(entity);

    return entity;
}

Entity* PongGame::loadResult(const char *name) const
{
    auto object = m_tmxLevel->getObjectGroup("scores")->getObject(name);
    auto entity = addEntity(name);

    addComponent<ContainerComponent>(entity)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    addComponent<TextComponent>(entity);
    getComponent<TextComponent>(entity)->setLayout(TextLayout::CenterCenter);
    getComponent<TextComponent>(entity)->setFontFromMemory(
        renderer(),
        default_font,
        default_font_size,
        63
    );

    return entity;
}

Entity* PongGame::loadInstruction(const char *name, const char *text)
{
    auto object = m_tmxLevel->getObjectGroup("instructions")->getObject(name);
    auto entity = addEntity(name);

    addComponent<ContainerComponent>(entity)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    addComponent<TextComponent>(entity);
    getComponent<TextComponent>(entity)->setLayout(TextLayout::LeftCenter);
    getComponent<TextComponent>(entity)->setText(text);
    getComponent<TextComponent>(entity)->setForeground(Color_DarkGrey);
    getComponent<TextComponent>(entity)->setFontFromMemory(
        renderer(),
        default_font,
        default_font_size,
        27
    );

    return entity;
}
