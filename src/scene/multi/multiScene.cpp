//
// gameScene.cpp
// pong
//
// Created by Damien Bendejacq on 13/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "multiScene.hpp"
#include "multiConst.hpp"
#include "state/multiServiceState.hpp"
#include "state/multiGameState.hpp"
#include "state/multiGameOverState.hpp"
#include "../menu/menuScene.hpp"

IMPORT_TEXT_RESOURCE(multi_tmx)
IMPORT_BINARY_RESOURCE(tileset_png)
IMPORT_BINARY_RESOURCE(default_font)
IMPORT_BINARY_RESOURCE(left_wav)
IMPORT_BINARY_RESOURCE(right_wav)
IMPORT_BINARY_RESOURCE(wall_wav)

MultiScene::MultiScene(Application& application, SceneManager<Scene>& sceneManager)
    : Scene(application, sceneManager)
{
    TmxSceneLoader sceneLoader {*this, multi_tmx, tileset_png, tileset_png_size, default_font, default_font_size};

    configure(sceneLoader);

    m_stateMachine.addState<MultiServiceState>(*this, sceneLoader);
    m_stateMachine.addState<MultiGameState>(*this, sceneLoader);
    m_stateMachine.addState<MultiGameOverState>(*this, sceneLoader);
    m_stateMachine.start();
}

void MultiScene::frame(float delta)
{
    handlePaddleMotion(m_leftPaddleVelocity, KeyboardKey::S, KeyboardKey::X);
    handlePaddleMotion(m_rightPaddleVelocity, KeyboardKey::P, KeyboardKey::L);

    m_stateMachine.frame(delta);

    if (input().keyPress(KeyboardKey::Escape))
    {
        loadScene<MenuScene>();
    }
}

void MultiScene::handlePaddleMotion(Velocity *velocity, KeyboardKey upKey, KeyboardKey downKey)
{
    auto up = input().keyDown(upKey);
    auto down = input().keyDown(downKey);

    if (up ^ down)
    {
        velocity->set(0.0f, up ? -MultiConst::PaddleSpeed : MultiConst::PaddleSpeed);
    }
    else
    {
        velocity->set(0.0f, 0.0f);
    }
}

void MultiScene::configure(const TmxSceneLoader& sceneLoader)
{
    auto& aabbCollisionSystem = getSystem<AABBCollisionSystem>();
    aabbCollisionSystem.addGroup("paddle", "wall");
    aabbCollisionSystem.addGroup("ball", "paddle");
    aabbCollisionSystem.addGroup("ball", "wall");

    // Left paddle
    {
        auto paddle = sceneLoader.entity("left_paddle");
        addComponent<Velocity>(paddle);
        addComponent<Tag>(paddle, "paddle");
        addComponent<AudioSource>(paddle, left_wav, left_wav_size);
        addComponent<Numerical<bool>>(paddle, false);

        m_leftPaddleVelocity = &getComponent<Velocity>(paddle);
    }

    // Right paddle
    {
        auto paddle = sceneLoader.entity("right_paddle");
        addComponent<Velocity>(paddle);
        addComponent<Tag>(paddle, "paddle");
        addComponent<AudioSource>(paddle, right_wav, right_wav_size);
        addComponent<Numerical<bool>>(paddle, false);

        m_rightPaddleVelocity = &getComponent<Velocity>(paddle);
    }

    // Top wall
    {
        auto wall = sceneLoader.entity("top_wall");
        addComponent<Velocity>(wall);
        addComponent<Tag>(wall, "wall");
        addComponent<AudioSource>(wall, wall_wav, wall_wav_size);
    }

    // Bottom wall
    {
        auto wall = sceneLoader.entity("bottom_wall");
        addComponent<Velocity>(wall);
        addComponent<Tag>(wall, "wall");
        addComponent<AudioSource>(wall, wall_wav, wall_wav_size);
    }

    // Ball
    {
        auto ball = sceneLoader.entity("ball");
        addComponent<Velocity>(ball);
        addComponent<Tag>(ball, "ball");
        addComponent<Numerical<int>>(ball, MultiConst::BallSpeedMin);
    }

    // Left score
    {
        auto score = sceneLoader.entity("left_score");
        addComponent<Numerical<int>>(score, 0);
    }

    // Right score
    {
        auto score = sceneLoader.entity("right_score");
        addComponent<Numerical<int>>(score, 0);
    }

    disableEntity(sceneLoader.entity("game_over"));
    disableEntity(sceneLoader.entity("left_result"));
    disableEntity(sceneLoader.entity("right_result"));
    disableEntity(sceneLoader.entity("terminate_game_instruction"));
}
