//
// velocityComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __VELOCITY_COMPONENT_H__
#define __VELOCITY_COMPONENT_H__

#include "component/component.hpp"
#include "core/math/vector2d.hpp"

namespace Jackbengine {

class VelocityComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(VelocityComponent)

public:
    VelocityComponent() = default;
    VelocityComponent(float x, float y);

    ~VelocityComponent() override = default;

    const Vec2f& get() const;
    void set(float x, float y);

    float x() const;
    void setX(float x);

    float y() const;
    void setY(float y);

private:
    Vec2f m_velocity;
};

using Velocity = VelocityComponent;

} // namespace Jackbengine

#endif // __VELOCITY_COMPONENT_H__
