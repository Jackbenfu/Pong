//
// gameSceneLoader.cpp
// Pong
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright © 2016 Damien Bendejacq. All rights reserved.
//

#include "gameSceneLoader.h"

using namespace Jackbengine;

IMPORT_BINARY_RESOURCE(left_wav)
IMPORT_BINARY_RESOURCE(right_wav)
IMPORT_BINARY_RESOURCE(wall_wav)
IMPORT_BINARY_RESOURCE(default_font)
IMPORT_BINARY_RESOURCE(tileset_png)

GameSceneLoader::GameSceneLoader(Scene *scene)
    : TmxSceneLoader(scene)
{
    // Nothing
}

GameSceneLoader::~GameSceneLoader() = default;

int GameSceneLoader::getMaxScore() const
{
    static int maxScore;
    map()->getProperties()->getIntProperty("maxScore", &maxScore);

    return maxScore;
}

bool GameSceneLoader::loadContents()
{
    addResourceDependency(TILESET_FILE, tileset_png, tileset_png_size);

    createImageEntityFromLayer("background", TILESET_FILE);

    loadWall("top_wall");
    loadWall("bottom_wall");
    loadPaddle("left_paddle", left_wav, left_wav_size);
    loadPaddle("right_paddle", right_wav, right_wav_size);
    loadBall();
    loadScore("left_score");
    loadScore("right_score");
    loadGameOver();
    loadResult("left_result");
    loadResult("right_result");

    createTextEntityFromObject("instructions", "left_paddle_instruction_1");
    createTextEntityFromObject("instructions", "left_paddle_instruction_2");
    createTextEntityFromObject("instructions", "right_paddle_instruction_1");
    createTextEntityFromObject("instructions", "right_paddle_instruction_2");
    createTextEntityFromObject("instructions", "launch_ball_instruction_1");
    createTextEntityFromObject("instructions", "launch_ball_instruction_2");
    createTextEntityFromObject("instructions", "goal_1");

    createTextEntityFromObject("instructions", "goal_2");
    auto goal2 = scene()->getEntity("goal_2");
    auto goal2Text = scene()->getComponent<TextComponent>(goal2);
    memset(m_goal2Text, 0, GOAL2_TEXT_SIZE);
    sprintf(m_goal2Text, goal2Text->getText().c_str(), getMaxScore());
    goal2Text->setText(m_goal2Text);

    createTextEntityFromObject("scores", "terminate_game_instruction");
    auto terminateGameInstruction = scene()->getEntity("terminate_game_instruction");
    scene()->disableEntity(terminateGameInstruction);

    loadSystems();

    return true;
}

void GameSceneLoader::loadSystems()
{
    scene()->addSystem<MotionSystem>();

    auto aabbCollisionSystem = scene()->addSystem<AABBCollisionSystem>();
    aabbCollisionSystem->addCollisionGroup("paddle", "wall");
    aabbCollisionSystem->addCollisionGroup("ball", "paddle");
    aabbCollisionSystem->addCollisionGroup("ball", "wall");

    auto spriteRenderSystem = scene()->addSystem<SpriteRenderSystem>();
    spriteRenderSystem->setRenderer(scene()->renderer());

    auto textRenderSystem = scene()->addSystem<TextRenderSystem>();
    textRenderSystem->setRenderer(scene()->renderer());
}

void GameSceneLoader::loadWall(const char *name)
{
    auto objectGroup = map()->getObjectGroup(name);
    auto shape = objectGroup->getObject("shape");

    auto entity = scene()->addEntity(name);

    scene()->addComponent<TransformComponent>(entity)->setPosition(
        static_cast<float>(shape->getX()),
        static_cast<float>(shape->getY())
    );
    scene()->addComponent<TagComponent>(entity)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    scene()->addComponent<BoxShapeComponent>(entity)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    scene()->addComponent<AudioSourceComponent>(entity)->loadFromMemory(
        wall_wav,
        wall_wav_size
    );
    scene()->addComponent<VelocityComponent>(entity);
}

void GameSceneLoader::loadPaddle(const char *name, const void *soundData, size_t soundDataSize)
{
    auto objectGroup = map()->getObjectGroup(name);
    auto shape = objectGroup->getObject("shape");

    auto entity = scene()->addEntity(name);

    scene()->addComponent<TransformComponent>(entity)->setPosition(
        static_cast<float>(shape->getX()),
        static_cast<float>(shape->getY())
    );
    scene()->addComponent<TagComponent>(entity)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    scene()->addComponent<BoxShapeComponent>(entity)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    scene()->addComponent<AudioSourceComponent>(entity)->loadFromMemory(
        soundData,
        soundDataSize
    );
    scene()->addComponent<SpriteComponent>(entity)->loadFromObjectGroup(
        scene()->renderer(),
        map(),
        name,
        tileset_png,
        tileset_png_size
    );
    scene()->addComponent<VelocityComponent>(entity);
}

void GameSceneLoader::loadBall()
{
    auto objectGroup = map()->getObjectGroup("ball");
    auto shape = objectGroup->getObject("shape");

    auto entity = scene()->addEntity("ball");

    scene()->addComponent<TagComponent>(entity)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    scene()->addComponent<BoxShapeComponent>(entity)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    scene()->addComponent<SpriteComponent>(entity)->loadFromObjectGroup(
        scene()->renderer(),
        map(),
        "ball",
        tileset_png,
        tileset_png_size
    );
    scene()->addComponent<UintComponent>(entity); // Stores ball's speed
    scene()->addComponent<TransformComponent>(entity);
    scene()->addComponent<VelocityComponent>(entity);
}

void GameSceneLoader::loadScore(const char *name)
{
    auto object = map()->getObjectGroup("scores")->getObject(name);

    auto entity = scene()->addEntity(name);

    scene()->addComponent<ContainerComponent>(entity)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );
    scene()->addComponent<TransformComponent>(entity);
    scene()->addComponent<UintComponent>(entity); // Stores player's score

    auto text = scene()->addComponent<TextComponent>(entity);
    text->setText("0");
    text->setLayout(TextLayout::CenterCenter);
    text->setFontFromMemory(
        scene()->renderer(),
        default_font,
        default_font_size,
        54
    );
}

void GameSceneLoader::loadGameOver()
{
    auto object = map()->getObjectGroup("scores")->getObject("game_over");

    auto entity = scene()->addEntity("game_over");

    scene()->addComponent<ContainerComponent>(entity)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = scene()->addComponent<TextComponent>(entity);
    text->setText("GAME OVER");
    text->setLayout(TextLayout::CenterCenter);
    text->setFontFromMemory(
        scene()->renderer(),
        default_font,
        default_font_size,
        90
    );

    scene()->disableEntity(entity);
}

void GameSceneLoader::loadResult(const char *name)
{
    auto object = map()->getObjectGroup("scores")->getObject(name);

    auto entity = scene()->addEntity(name);

    scene()->addComponent<ContainerComponent>(entity)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = scene()->addComponent<TextComponent>(entity);
    text->setLayout(TextLayout::CenterCenter);
    text->setFontFromMemory(
        scene()->renderer(),
        default_font,
        default_font_size,
        63
    );
}
