//
// spriteComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 02/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "spriteComponent.hpp"

using namespace Jackbengine;

SpriteComponent::SpriteComponent(const Renderer& renderer, const std::string& file)
    : m_texture {renderer, file}
{ }

SpriteComponent::SpriteComponent(const Renderer& renderer, const void *data, size_t dataSize)
    : m_texture {renderer, data, dataSize}
{ }

SpriteComponent::SpriteComponent(const Renderer& renderer, int width, int height, Color32 color)
    : m_texture {renderer, width, height, color}
{ }

SpriteComponent::SpriteComponent(const Renderer& renderer, const TmxMap& map, const TmxLayer& layer,
                                   const void *tilesetImageData, size_t tilesetImageDataSize)
    : m_texture {renderer, map, layer, tilesetImageData, tilesetImageDataSize}
{ }

SpriteComponent::SpriteComponent(const Renderer& renderer, const TmxMap& map, const TmxObjectGroup& objectGroup,
                                   const void *tilesetImageData, size_t tilesetImageDataSize)
    : m_texture {renderer, map, objectGroup, tilesetImageData, tilesetImageDataSize}
{ }

const Texture& SpriteComponent::texture() const
{
    return m_texture;
}
