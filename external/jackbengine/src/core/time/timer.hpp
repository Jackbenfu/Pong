//
// timer.hpp
// jackbengine
//
// Created by Damien Bendejacq on 10/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __TIMER_H__
#define __TIMER_H__

#include <memory>
#include "common.hpp"

namespace Jackbengine {

class Timer
{
    DISALLOW_COPY_AND_MOVE(Timer)

public:
    explicit Timer(uint fps);
    ~Timer();

    void start();
    void snapshot();

    uint elapsedMilliseconds() const;
    uint effectiveElapsedMilliseconds() const;

    int fps() const;

    bool isFixedFps() const;
    int fixedFps() const;
    void enableFixedFps(uint fps);
    void disableFixedFps();

    uint totalFrames() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace Jackbengine

#endif // __TIMER_H__
