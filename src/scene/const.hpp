//
// const.hpp
// pong
//
// Created by Damien Bendejacq on 15/11/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __CONST_H__
#define __CONST_H__

namespace Const
{

constexpr int ScoreToWin = 9;

constexpr float PaddleSpeed = 400.0f;

constexpr int BallSpeedMin = 500;
constexpr int BallSpeedMax = 750;
constexpr int BallSpeedIncr = 5;

constexpr int BallOutOfScreenShift = 200;

const Color32 WinColor = Color32(69, 183, 130);
const Color32 LoseColor = Color32(196, 89, 73);

const std::string WinText = "WIN";
const std::string LoseText = "LOSE";

}

#endif // __CONST_H__
