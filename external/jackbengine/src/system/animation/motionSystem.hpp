//
// motionSystem.hpp
// jackbengine
//
// Created by Damien Bendejacq on 09/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __MOTION_SYSTEM_H__
#define __MOTION_SYSTEM_H__

#include "system/system.hpp"

namespace Jackbengine {

class MotionSystem final : public System
{
    DISALLOW_COPY_AND_MOVE(MotionSystem)

public:
    MotionSystem() = default;

    int order() const final;

private:
    void frame(float delta) override;
    bool hasRequiredComponents(ComponentCollection& components) const override;
};

} // namespace Jackbengine

#endif // __MOTION_SYSTEM_H__
