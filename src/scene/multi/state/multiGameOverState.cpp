//
// multiGameOverState.cpp
// pong
//
// Created by Damien Bendejacq on 02/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "multiGameOverState.hpp"
#include "../../menu/menuScene.hpp"
#include "../multiConst.hpp"

MultiGameOverState::MultiGameOverState(StateMachine& stateMachine, Scene& scene, TmxSceneLoader& sceneLoader)
    : SceneState(stateMachine, scene),
      m_leftScore {sceneLoader.entity("left_score")},
      m_rightScore {sceneLoader.entity("right_score")},
      m_leftResult {sceneLoader.entity("left_result")},
      m_rightResult {sceneLoader.entity("right_result")},
      m_gameOver {sceneLoader.entity("game_over")},
      m_terminateGameInstruction {sceneLoader.entity("terminate_game_instruction")}
{ }

void MultiGameOverState::enter()
{
    enableEntity(m_gameOver);
    enableEntity(m_leftResult);
    enableEntity(m_rightResult);
    enableEntity(m_terminateGameInstruction);

    auto& leftResultText = getComponent<Text>(m_leftResult);
    auto& rightResultText = getComponent<Text>(m_rightResult);

    auto& leftScore = getComponent<Numerical<int>>(m_leftScore);
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

void MultiGameOverState::frame(float)
{
    if (input().keyPress(KeyboardKey::Space))
    {
        loadScene<MenuScene>();
    }
}
