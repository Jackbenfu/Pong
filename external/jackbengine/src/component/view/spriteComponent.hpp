//
// spriteComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 02/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SPRITE_COMPONENT_H__
#define __SPRITE_COMPONENT_H__

#include "component/component.hpp"
#include "core/render/renderer/renderer.hpp"
#include "core/render/texture/texture.hpp"

namespace Jackbengine {

class SpriteComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(SpriteComponent)

public:
    SpriteComponent(const Renderer& renderer, const std::string& file);
    SpriteComponent(const Renderer& renderer, const void *data, size_t dataSize);
    SpriteComponent(const Renderer& renderer, int width, int height, Color32 color);
    SpriteComponent(const Renderer& renderer, const TmxMap& map, const TmxLayer& layer,
                     const void *tilesetImageData, size_t tilesetImageDataSize);
    SpriteComponent(const Renderer& renderer, const TmxMap& map, const TmxObjectGroup& objectGroup,
                     const void *tilesetImageData, size_t tilesetImageDataSize);

    ~SpriteComponent() override = default;

    const Texture& texture() const;

private:
    Texture m_texture;
};

using Sprite = SpriteComponent;

} // namespace Jackbengine

#endif // __SPRITE_COMPONENT_H__
