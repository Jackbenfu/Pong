//
// texture.cpp
// jackbengine
//
// Created by Damien Bendejacq on 13/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "core/tmx/tmxMap.hpp"
#include "texture.hpp"
#include "texture.impl.hpp"

using namespace Jackbengine;

Texture::Texture(const Renderer& renderer, const std::string& file)
    : m_impl {std::make_unique<Impl>(renderer, file)}
{ }

Texture::Texture(const Renderer& renderer, const void *data, size_t dataSize)
    : m_impl {std::make_unique<Impl>(renderer, data, dataSize)}
{ }

Texture::Texture(const Renderer& renderer, int width, int height, Color32 color)
    : m_impl {std::make_unique<Impl>(renderer, width, height, color)}
{ }

Texture::Texture(const Renderer& renderer, const TmxMap& map, const TmxLayer& layer,
                   const void *tilesetImageData, size_t tilesetImageDataSize)
    : m_impl {std::make_unique<Impl>(renderer, map, layer, tilesetImageData, tilesetImageDataSize)}
{ }

Texture::Texture(const Renderer& renderer, const TmxMap& map, const TmxObjectGroup& objectGroup,
                   const void *tilesetImageData, size_t tilesetImageDataSize)
    : m_impl {std::make_unique<Impl>(renderer, map, objectGroup, tilesetImageData, tilesetImageDataSize)}
{ }

Texture::Texture(const Renderer& renderer, const Font& font,
                   const std::string& text, Color32 foreground)
    : m_impl {std::make_unique<Impl>(renderer, font, text, foreground)}
{ }

Texture::~Texture() = default;

int Texture::width() const
{
    return m_impl->width();
}

int Texture::height() const
{
    return m_impl->height();
}

void* Texture::internalObject() const
{
    return m_impl->internalObject();
}
