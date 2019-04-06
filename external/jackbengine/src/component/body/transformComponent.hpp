//
// transformComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__

#include "component/component.hpp"
#include "core/math/vector2d.hpp"

namespace Jackbengine {

class TransformComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(TransformComponent)

public:
    TransformComponent() = default;
    TransformComponent(float positionX, float positionY);
    TransformComponent(float positionX, float positionY, double angle);
    TransformComponent(float positionX, float positionY, float scaleX, float scaleY);
    TransformComponent(float positionX, float positionY, float scaleX, float scaleY, double angle);

    ~TransformComponent() override = default;

    const Vec2f& position() const;
    float positionX() const;
    float positionY() const;
    void setPosition(float x, float y);
    void setPositionX(float x);
    void setPositionY(float y);

    double angle() const;
    void setAngle(double angle);

    const Vec2f& scale() const;
    float scaleX() const;
    float scaleY() const;
    void setScale(float x, float y);
    void setScaleX(float x);
    void setScaleY(float y);

private:
    Vec2f m_position;
    Vec2f m_scale;
    double m_angle {0.0};
};

using Transform = TransformComponent;

} // namespace Jackbengine

#endif // __TRANSFORM_COMPONENT_H__
