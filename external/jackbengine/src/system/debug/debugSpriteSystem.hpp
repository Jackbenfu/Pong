//
// debugSpriteSystem.hpp
// jackbengine
//
// Created by Damien Bendejacq on 19/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __DEBUG_SPRITE_SYSTEM_H__
#define __DEBUG_SPRITE_SYSTEM_H__

#include "system/system.hpp"
#include "core/render/renderer/renderer.hpp"

namespace Jackbengine {

class DebugSpriteSystem final : public System
{
    DISALLOW_COPY_AND_MOVE(DebugSpriteSystem)

public:
    DebugSpriteSystem() = delete;
    explicit DebugSpriteSystem(Renderer& renderer);
    ~DebugSpriteSystem() override = default;

    int order() const final;

private:
    void frame(float delta) override;
    bool hasRequiredComponents(ComponentCollection& components) const override;

    Renderer& m_renderer;
    const Color32 m_color;
};

} // namespace Jackbengine

#endif // __DEBUG_SPRITE_SYSTEM_H__
