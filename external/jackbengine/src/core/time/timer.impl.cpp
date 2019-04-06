//
// timer.impl.cpp
// jackbengine
//
// Created by Damien Bendejacq on 10/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "timer.impl.hpp"
#include "platform.hpp"

using namespace Jackbengine;

Timer::Impl::Impl(uint fps)
{
    enableFixedFps(fps);
}

void Timer::Impl::start()
{
    m_start = ticks();
}

void Timer::Impl::snapshot()
{
    ++m_totalFrames;

    m_elapsedMilliseconds = ticks() - m_start;
    m_effectiveElapsedMilliseconds = m_elapsedMilliseconds;
    uint delayTime = 0;

    if (0 < m_fixedFps && m_elapsedMilliseconds < m_fixedFpsDelayTime)
    {
        delayTime = m_fixedFpsDelayTime - m_elapsedMilliseconds;
        m_elapsedMilliseconds += delayTime;
    }

    if (1000 < m_fpsElapsedMilliseconds)
    {
        m_fps = m_fpsTemp;
        m_fpsElapsedMilliseconds = 0;
        m_fpsTemp = 0;
    }
    else
    {
        m_fpsElapsedMilliseconds += m_elapsedMilliseconds;
        ++m_fpsTemp;
    }

    if (0 < delayTime)
    {
        delay(delayTime);
    }
}

uint Timer::Impl::elapsedMilliseconds() const
{
    return m_elapsedMilliseconds;
}

uint Timer::Impl::effectiveElapsedMilliseconds() const
{
    return m_effectiveElapsedMilliseconds;
}

int Timer::Impl::fps() const
{
    return m_fps;
}

bool Timer::Impl::isFixedFps() const
{
    return 0 < m_fixedFps;
}

int Timer::Impl::fixedFps() const
{
    return m_fixedFps;
}

void Timer::Impl::enableFixedFps(uint fps)
{
    if (0 >= fps)
    {
        fps = 60; // Defaulting to 60 fps
    }

    m_fixedFps = fps;
    m_fixedFpsDelayTime = 1000 / fps;
}

void Timer::Impl::disableFixedFps()
{
    m_fixedFps = 0;
}

uint Timer::Impl::totalFrames() const
{
    return m_totalFrames;
}

void Timer::Impl::delay(uint ms) const
{
#ifndef EMSCRIPTEN
    SDL_Delay(ms);
#else
    (void)ms;
#endif
}

uint Timer::Impl::ticks() const
{
    return SDL_GetTicks();
}
