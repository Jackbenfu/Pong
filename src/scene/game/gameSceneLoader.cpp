//
// gameSceneLoader.cpp
// Jackbengine
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright (c) 2016 Damien Bendejacq. All rights reserved.
//

#include "gameSceneLoader.h"

IMPORT_BINARY_RESOURCE(left_wav)
IMPORT_BINARY_RESOURCE(right_wav)
IMPORT_BINARY_RESOURCE(wall_wav)
IMPORT_BINARY_RESOURCE(default_font)
IMPORT_BINARY_RESOURCE(tileset_png)

GameSceneLoader::GameSceneLoader(Scene *scene)
    : TmxSceneLoader(scene)
{
}

GameSceneLoader::~GameSceneLoader()
{
    DELETE_SAFE(m_goal2Text);
}

int GameSceneLoader::getMaxScore() const
{
    static int maxScore;
    map()->getProperties()->getIntProperty("maxScore", &maxScore);

    return maxScore;
}

bool GameSceneLoader::loadContents()
{
    loadBackground();
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
    loadInstruction(
        "instructions", "left_paddle_instruction_1", "E or C:", TextLayout::RightCenter, Color_YellowGold);
    loadInstruction(
        "instructions", "left_paddle_instruction_2", "move left paddle", TextLayout::LeftCenter, Color_DarkGrey);
    loadInstruction(
        "instructions", "right_paddle_instruction_1", "UP or DOWN:", TextLayout::RightCenter, Color_YellowGold);
    loadInstruction(
        "instructions", "right_paddle_instruction_2", "move right paddle", TextLayout::LeftCenter, Color_DarkGrey);
    loadInstruction(
        "instructions", "launch_ball_instruction_1", "SPACEBAR:", TextLayout::RightCenter, Color_YellowGold);
    loadInstruction(
        "instructions", "launch_ball_instruction_2", "launch the ball", TextLayout::LeftCenter, Color_DarkGrey);
    loadInstruction(
        "instructions", "goal_1", "Goal:", TextLayout::RightCenter, Color_YellowGold);

    m_goal2Text = new char[30];
    memset(m_goal2Text, 0, 30);
    sprintf(m_goal2Text, "reach %d points!", getMaxScore());
    loadInstruction(
        "instructions", "goal_2", m_goal2Text, TextLayout::LeftCenter, Color_DarkGrey);

    auto terminateGameInstruction = loadInstruction(
        "scores", "terminate_game_instruction", "Press SPACEBAR...", TextLayout::CenterCenter, Color_DarkGrey);
    DISABLE_ENTITY(terminateGameInstruction);

    loadSystems();

    return true;
}

void GameSceneLoader::loadSystems()
{
    ADD_SYSTEM(MotionSystem);

    auto aabbCollisionSystem = ADD_SYSTEM(AABBCollisionSystem);
    aabbCollisionSystem->addCollisionGroup("paddle", "wall");
    aabbCollisionSystem->addCollisionGroup("ball", "paddle");
    aabbCollisionSystem->addCollisionGroup("ball", "wall");

    auto spriteRenderSystem = ADD_SYSTEM(SpriteRenderSystem);
    spriteRenderSystem->setRenderer(m_scene->renderer());

    auto textRenderSystem = ADD_SYSTEM(TextRenderSystem);
    textRenderSystem->setRenderer(m_scene->renderer());
}

void GameSceneLoader::loadBackground()
{
    auto entity = ADD_ENTITY("background");

    ADD_COMPONENT(entity, SpriteComponent)->loadFromLayer(
        m_scene->renderer(),
        map(),
        "background",
        tileset_png,
        tileset_png_size
    );
    ADD_COMPONENT(entity, TransformComponent);
}

void GameSceneLoader::loadWall(const char *name)
{
    auto objectGroup = map()->getObjectGroup(name);
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
}

void GameSceneLoader::loadPaddle(const char *name, const void *soundData, size_t soundDataSize)
{
    auto objectGroup = map()->getObjectGroup(name);
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
        soundData,
        soundDataSize
    );
    ADD_COMPONENT(entity, SpriteComponent)->loadFromObjectGroup(
        m_scene->renderer(),
        map(),
        name,
        tileset_png,
        tileset_png_size
    );
    ADD_COMPONENT(entity, VelocityComponent);
}

void GameSceneLoader::loadBall()
{
    auto objectGroup = map()->getObjectGroup("ball");
    auto shape = objectGroup->getObject("shape");

    auto entity = ADD_ENTITY("ball");

    ADD_COMPONENT(entity, TagComponent)->setTag(
        objectGroup->getProperties()->getProperty("tag")
    );
    ADD_COMPONENT(entity, BoxShapeComponent)->setSize(
        static_cast<float>(shape->getWidth()),
        static_cast<float>(shape->getHeight())
    );
    ADD_COMPONENT(entity, SpriteComponent)->loadFromObjectGroup(
        m_scene->renderer(),
        map(),
        "ball",
        tileset_png,
        tileset_png_size
    );
    ADD_COMPONENT(entity, UintComponent); // Stores ball's speed
    ADD_COMPONENT(entity, TransformComponent);
    ADD_COMPONENT(entity, VelocityComponent);
}

void GameSceneLoader::loadScore(const char *name)
{
    auto object = map()->getObjectGroup("scores")->getObject(name);

    auto entity = ADD_ENTITY(name);

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
        m_scene->renderer(),
        default_font,
        default_font_size,
        54
    );
}

void GameSceneLoader::loadGameOver()
{
    auto object = map()->getObjectGroup("scores")->getObject("game_over");

    auto entity = ADD_ENTITY("game_over");

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
        m_scene->renderer(),
        default_font,
        default_font_size,
        90
    );

    DISABLE_ENTITY(entity);
}

void GameSceneLoader::loadResult(const char *name)
{
    auto object = map()->getObjectGroup("scores")->getObject(name);

    auto entity = ADD_ENTITY(name);

    ADD_COMPONENT(entity, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto text = ADD_COMPONENT(entity, TextComponent);
    text->setLayout(TextLayout::CenterCenter);
    text->setFontFromMemory(
        m_scene->renderer(),
        default_font,
        default_font_size,
        63
    );
}

Entity* GameSceneLoader::loadInstruction(
    const char *group, const char *name, const char *text, TextLayout textLayout, Color color)
{
    auto object = map()->getObjectGroup(group)->getObject(name);

    auto entity = ADD_ENTITY(name);

    ADD_COMPONENT(entity, ContainerComponent)->setRect(
        object->getX(),
        object->getY(),
        object->getWidth(),
        object->getHeight()
    );

    auto textComponent = ADD_COMPONENT(entity, TextComponent);
    textComponent->setLayout(textLayout);
    textComponent->setText(text);
    textComponent->setForeground(color);
    textComponent->setFontFromMemory(
        m_scene->renderer(),
        default_font,
        default_font_size,
        27
    );

    return entity;
}
