//
// debugTextSystem.hpp
// jackbengine
//
// Created by Damien Bendejacq on 20/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __DEBUG_TEXT_SYSTEM_H__
#define __DEBUG_TEXT_SYSTEM_H__

#include "system/system.hpp"
#include "core/render/renderer/renderer.hpp"

namespace Jackbengine {

class DebugTextSystem final : public  System
{
    DISALLOW_COPY_AND_MOVE(DebugTextSystem)

public:
    explicit DebugTextSystem(Renderer& renderer);
    DebugTextSystem(Renderer& renderer, Color32 color);
    ~DebugTextSystem() override = default;

    int order() const final;

private:
    void frame(float delta) override;
    bool hasRequiredComponents(ComponentCollection& components) const override;

    Renderer& m_renderer;
    Color32 m_color;
};

} // namespace Jackbengine

#endif // __DEBUG_TEXT_SYSTEM_H__
