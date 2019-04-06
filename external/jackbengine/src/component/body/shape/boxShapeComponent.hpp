//
// boxShapeComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 28/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __BOX_SHAPE_COMPONENT_H__
#define __BOX_SHAPE_COMPONENT_H__

#include "component/component.hpp"
#include "core/math/vector2d.hpp"

namespace Jackbengine {

class BoxShapeComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(BoxShapeComponent)

public:
    BoxShapeComponent() = default;
    BoxShapeComponent(float width, float height);

    ~BoxShapeComponent() override = default;

    float width() const;
    float height() const;
    const Vec2f& size() const;

    void setWidth(float width);
    void setHeight(float height);
    void setSize(float width, float height);

private:
    Vec2f m_vector;
};

using BoxShape = BoxShapeComponent;

} // namespace Jackbengine

#endif // __BOX_SHAPE_COMPONENT_H__
