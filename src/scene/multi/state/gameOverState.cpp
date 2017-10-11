//
// gameOverState.cpp
// pong
//
// Created by Damien Bendejacq on 02/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "gameOverState.hpp"
#include "../../menu/menuScene.hpp"
#include "../const/multiConst.hpp"

GameOverState::GameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : State(stateMachine),
      m_scene {scene},
      m_leftScore {sceneLoader.entity("left_score")},
      m_rightScore {sceneLoader.entity("right_score")},
      m_leftResult {sceneLoader.entity("left_result")},
      m_rightResult {sceneLoader.entity("right_result")},
      m_gameOver {sceneLoader.entity("game_over")},
      m_terminateGameInstruction {sceneLoader.entity("terminate_game_instruction")}
{ }

void GameOverState::enter()
{
    m_scene.enableEntity(m_gameOver);
    m_scene.enableEntity(m_leftResult);
    m_scene.enableEntity(m_rightResult);
    m_scene.enableEntity(m_terminateGameInstruction);

    auto& leftResultText = m_scene.getComponent<Text>(m_leftResult);
    auto& rightResultText = m_scene.getComponent<Text>(m_rightResult);

    auto& leftScore = m_scene.getComponent<Numerical<int>>(m_leftScore);
    if (MultiConst::ScoreToWin == leftScore.get())
    {
        leftResultText.setText(MultiConst::WinText);
        leftResultText.setForeground(MultiConst::WinColor);
        rightResultText.setText(MultiConst::LoseText);
        rightResultText.setForeground(MultiConst::LoseColor);
    }
    else
    {
        leftResultText.setText(MultiConst::LoseText);
        leftResultText.setForeground(MultiConst::LoseColor);
        rightResultText.setText(MultiConst::WinText);
        rightResultText.setForeground(MultiConst::WinColor);
    }
}

void GameOverState::frame(float)
{
    if (m_scene.input().keyPress(KeyboardKey::Space))
    {
        m_scene.loadScene<MenuScene>();
    }
}
