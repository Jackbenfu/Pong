//
// wallGameOverState.cpp
// pong
//
// Created by Damien Bendejacq on 15/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "wallGameOverState.hpp"
#include "../../menu/menuScene.hpp"

WallGameOverState::WallGameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : SceneState(stateMachine, scene),
      m_gameOver {sceneLoader.entity("game_over")},
      m_terminateGameInstruction {sceneLoader.entity("terminate_game_instruction")}
{ }

void WallGameOverState::enter()
{
    enableEntity(m_gameOver);
    enableEntity(m_terminateGameInstruction);
}

void WallGameOverState::frame(float)
{
    if (input().keyPress(KeyboardKey::Space))
    {
        loadScene<MenuScene>();
    }
}
