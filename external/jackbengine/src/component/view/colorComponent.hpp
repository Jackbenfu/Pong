//
// colorComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 01/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __COLOR_COMPONENT_H__
#define __COLOR_COMPONENT_H__

#include "component/component.hpp"
#include "core/render/color32.hpp"

namespace Jackbengine {

class ColorComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(ColorComponent)

public:
    explicit ColorComponent(Color32 color);
    ColorComponent(byte red, byte green, byte blue, byte alpha);
    ColorComponent(byte red, byte green, byte blue);

    ~ColorComponent() override = default;

    Color32 getColor() const;

    byte red() const;
    void setRed(byte value);

    byte green() const;
    void setGreen(byte value);

    byte blue() const;
    void setBlue(byte value);

    byte alpha() const;
    void setAlpha(byte value);

private:
    Color32 m_color;
};

using Color = ColorComponent;

} // namespace Jackbengine

#endif // __COLOR_COMPONENT_H__
