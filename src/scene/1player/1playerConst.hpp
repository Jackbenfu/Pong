//
// 1playerConst.hpp
// pong
//
// Created by Damien Bendejacq on 05/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __1_PLAYER_CONST_H__
#define __1_PLAYER_CONST_H__

#include "jackbengine.hpp"

namespace OnePlayerConst
{

constexpr int ScoreToWin = 9;

constexpr float PaddleSpeed = 375.0f;

constexpr int BallSpeedMin = 500;
constexpr int BallSpeedMax = 750;
constexpr int BallSpeedIncr = 5;

constexpr int BallOutOfScreenShift = 200;

const Color32 WinColor = Color32(69, 183, 130);
const Color32 LoseColor = Color32(196, 89, 73);

const std::string WinText = "WIN";
const std::string LoseText = "LOSE";

}

#endif // __1_PLAYER_CONST_H__
