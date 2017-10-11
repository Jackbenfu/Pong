//
// multiConst.hpp
// pong
//
// Created by Damien Bendejacq on 05/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __MULTI_CONST_H__
#define __MULTI_CONST_H__

#include "jackbengine.hpp"

namespace MultiConst
{

constexpr int ScoreToWin = 5;

constexpr float PaddleSpeed = 500.0f;

constexpr int BallSpeedMin = 500;
constexpr int BallSpeedMax = 800;
constexpr int BallSpeedIncr = 5;

const Color32 WinColor = Color32(69, 183, 130);
const Color32 LoseColor = Color32(196, 89, 73);

const std::string WinText = "WIN";
const std::string LoseText = "LOSE";

}

#endif // __MULTI_CONST_H__
