//
// soloGameOverState.cpp
// pong
//
// Created by Damien Bendejacq on 15/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "soloGameOverState.hpp"
#include "../../menu/menuScene.hpp"

SoloGameOverState::SoloGameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : State(stateMachine),
      m_scene {scene},
      m_gameOver {sceneLoader.entity("game_over")},
      m_terminateGameInstruction {sceneLoader.entity("terminate_game_instruction")}
{ }

void SoloGameOverState::enter()
{
    m_scene.enableEntity(m_gameOver);
    m_scene.enableEntity(m_terminateGameInstruction);
}

void SoloGameOverState::frame(float)
{
    if (m_scene.input().keyPress(KeyboardKey::Space))
    {
        m_scene.loadScene<MenuScene>();
    }
}
