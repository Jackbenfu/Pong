//
// 2playersGameOverState.cpp
// pong
//
// Created by Damien Bendejacq on 02/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "2playersGameOverState.hpp"
#include "../../menu/menuScene.hpp"
#include "../2playersConst.hpp"

TwoPlayersGameOverState::TwoPlayersGameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : SceneState(stateMachine, scene),
      m_leftScore {sceneLoader.entity("left_score")},
      m_rightScore {sceneLoader.entity("right_score")},
      m_leftResult {sceneLoader.entity("left_result")},
      m_rightResult {sceneLoader.entity("right_result")},
      m_gameOver {sceneLoader.entity("game_over")},
      m_terminateGameInstruction {sceneLoader.entity("terminate_game_instruction")}
{ }

void TwoPlayersGameOverState::enter()
{
    enableEntity(m_gameOver);
    enableEntity(m_leftResult);
    enableEntity(m_rightResult);
    enableEntity(m_terminateGameInstruction);

    auto& leftResultText = getComponent<Text>(m_leftResult);
    auto& rightResultText = getComponent<Text>(m_rightResult);

    auto& leftScore = getComponent<Numerical<int>>(m_leftScore);
    if (TwoPlayersConst::ScoreToWin == leftScore.get())
    {
        leftResultText.setText(TwoPlayersConst::WinText);
        leftResultText.setForeground(TwoPlayersConst::WinColor);
        rightResultText.setText(TwoPlayersConst::LoseText);
        rightResultText.setForeground(TwoPlayersConst::LoseColor);
    }
    else
    {
        leftResultText.setText(TwoPlayersConst::LoseText);
        leftResultText.setForeground(TwoPlayersConst::LoseColor);
        rightResultText.setText(TwoPlayersConst::WinText);
        rightResultText.setForeground(TwoPlayersConst::WinColor);
    }
}

void TwoPlayersGameOverState::frame(float)
{
    if (input().keyPress(KeyboardKey::Space))
    {
        loadScene<MenuScene>();
    }
}
