//
// wallScene.cpp
// pong
//
// Created by Damien Bendejacq on 11/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "wallScene.hpp"
#include "wallConst.hpp"
#include "state/wallServiceState.hpp"
#include "state/wallGameState.hpp"
#include "state/wallGameOverState.hpp"
#include "../menu/menuScene.hpp"

IMPORT_TEXT_RESOURCE(wall_tmx)
IMPORT_BINARY_RESOURCE(tileset_png)
IMPORT_BINARY_RESOURCE(default_font)
IMPORT_BINARY_RESOURCE(left_wav)
IMPORT_BINARY_RESOURCE(right_wav)
IMPORT_BINARY_RESOURCE(wall_wav)

WallScene::WallScene(Application& application, SceneManager<Scene>& sceneManager)
    : Scene(application, sceneManager)
{
    TmxSceneLoader sceneLoader {*this, wall_tmx, tileset_png, tileset_png_size, default_font, default_font_size};

    configure(sceneLoader);

    m_stateMachine.addState<WallServiceState>(*this, sceneLoader);
    m_stateMachine.addState<WallGameState>(*this, sceneLoader);
    m_stateMachine.addState<WallGameOverState>(*this, sceneLoader);
    m_stateMachine.start();
}

void WallScene::frame(float delta)
{
    handlePaddleMotion(KeyboardKey::S, KeyboardKey::X);

    m_stateMachine.frame(delta);

    if (input().keyPress(KeyboardKey::Escape))
    {
        loadScene<MenuScene>();
    }
}

void WallScene::handlePaddleMotion(KeyboardKey upKey, KeyboardKey downKey)
{
    auto up = input().keyDown(upKey);
    auto down = input().keyDown(downKey);

    if (up ^ down)
    {
        m_paddleVelocity->set(0.0f, up ? -WallConst::PaddleSpeed : WallConst::PaddleSpeed);
    }
    else
    {
        m_paddleVelocity->set(0.0f, 0.0f);
    }
}

void WallScene::configure(const TmxSceneLoader& sceneLoader)
{
    auto& aabbCollisionSystem = getSystem<AABBCollisionSystem>();
    aabbCollisionSystem.addGroup("paddle", "wall");
    aabbCollisionSystem.addGroup("ball", "paddle");
    aabbCollisionSystem.addGroup("ball", "wall");

    // Paddle
    {
        auto paddle = sceneLoader.entity("paddle");
        addComponent<Velocity>(paddle);
        addComponent<Tag>(paddle, "paddle");
        addComponent<AudioSource>(paddle, left_wav, left_wav_size);

        m_paddleVelocity = &getComponent<Velocity>(paddle);
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

    // Right wall
    {
        auto wall = sceneLoader.entity("right_wall");
        addComponent<Velocity>(wall);
        addComponent<Tag>(wall, "wall");
        addComponent<AudioSource>(wall, right_wav, right_wav_size);
    }

    // Ball
    {
        auto ball = sceneLoader.entity("ball");
        addComponent<Velocity>(ball);
        addComponent<Tag>(ball, "ball");
        addComponent<Numerical<int>>(ball, WallConst::BallSpeedMin);
    }

    // Score
    {
        auto score = sceneLoader.entity("score");
        addComponent<Numerical<int>>(score, 0);
    }

    disableEntity(sceneLoader.entity("game_over"));
    disableEntity(sceneLoader.entity("terminate_game_instruction"));
}
