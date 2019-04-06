//
// timer.cpp
// jackbengine
//
// Created by Damien Bendejacq on 10/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "timer.hpp"
#include "timer.impl.hpp"

using namespace Jackbengine;

Timer::Timer(uint fps)
    : m_impl {std::make_unique<Impl>(fps)}
{ }

Timer::~Timer() = default;

void Timer::start()
{
    m_impl->start();
}

void Timer::snapshot()
{
    m_impl->snapshot();
}

uint Timer::elapsedMilliseconds() const
{
    return m_impl->elapsedMilliseconds();
}

uint Timer::effectiveElapsedMilliseconds() const
{
    return m_impl->effectiveElapsedMilliseconds();
}

int Timer::fps() const
{
    return m_impl->fps();
}

bool Timer::isFixedFps() const
{
    return m_impl->isFixedFps();
}

int Timer::fixedFps() const
{
    return m_impl->fixedFps();
}

void Timer::enableFixedFps(uint fps)
{
    m_impl->enableFixedFps(fps);
}

void Timer::disableFixedFps()
{
    m_impl->disableFixedFps();
}

uint Timer::totalFrames() const
{
    return m_impl->totalFrames();
}
