//
// wallConst.hpp
// pong
//
// Created by Damien Bendejacq on 11/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __WALL_CONST_H__
#define __WALL_CONST_H__

#include "jackbengine.hpp"

namespace WallConst
{

constexpr float PaddleSpeed = 375.0f;

constexpr int BallSpeedMin = 500;
constexpr int BallSpeedMax = 750;
constexpr int BallSpeedIncr = 5;

constexpr int BallOutOfScreenShift = 200;

}

#endif // __WALL_CONST_H__
