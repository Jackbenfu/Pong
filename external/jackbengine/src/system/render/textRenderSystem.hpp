//
// textRenderSystem.hpp
// jackbengine
//
// Created by Damien Bendejacq on 21/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __TEXT_RENDER_SYSTEM_H__
#define __TEXT_RENDER_SYSTEM_H__

#include "system/system.hpp"
#include "core/render/renderer/renderer.hpp"

namespace Jackbengine {

class TextRenderSystem final : public System
{
    DISALLOW_COPY_AND_MOVE(TextRenderSystem)

public:
    TextRenderSystem() = delete;
    explicit TextRenderSystem(Renderer& renderer);
    ~TextRenderSystem() override = default;

    int order() const final;

private:
    void frame(float delta) override;
    bool hasRequiredComponents(ComponentCollection& components) const override;

    Renderer& m_renderer;
};

} // namespace Jackbengine

#endif // __TEXT_RENDER_SYSTEM_H__
