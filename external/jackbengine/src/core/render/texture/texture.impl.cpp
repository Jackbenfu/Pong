//
// texture.impl.cpp
// jackbengine
//
// Created by Damien Bendejacq on 13/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "texture.impl.hpp"
#include "core/render/renderer/renderer.hpp"

using namespace Jackbengine;

Texture::Impl::Impl(const Renderer& renderer, const std::string& file)
{
    const auto sdlSurface = std::make_unique<SdlSurface>(file);

    loadTextureFromSurface(renderer, *sdlSurface);
}

Texture::Impl::Impl(const Renderer& renderer, const void *data, size_t dataSize)
{
    const auto sdlRwops = std::make_unique<SdlRwops>(data, dataSize);
    const auto sdlSurface = std::make_unique<SdlSurface>(*sdlRwops);

    loadTextureFromSurface(renderer, *sdlSurface);
}

Texture::Impl::Impl(const Renderer& renderer, int width, int height, Color32 color)
{
    const auto sdlSurface = std::make_unique<SdlSurface>(width, height, 32);
    const auto sdlSurfaceObject = sdlSurface->internalObject();

    const auto rgbUint = SDL_MapRGB(sdlSurfaceObject->format, color.r, color.g, color.b);
    if (SDL_FillRect(sdlSurfaceObject, nullptr, rgbUint) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }

    loadTextureFromSurface(renderer, *sdlSurface);
}

Texture::Impl::Impl(const Renderer& renderer, const TmxMap& map, const TmxLayer& layer,
                     const void *tilesetImageData, size_t tilesetImageDataSize)
{
    const auto tileset = map.tileset();

    const auto sdlRwops = std::make_unique<SdlRwops>(tilesetImageData, tilesetImageDataSize);
    const auto sdlTilesetSurface = std::make_unique<SdlSurface>(*sdlRwops);
    const auto sdlTilesetSurfaceObject = sdlTilesetSurface->internalObject();

    const auto layerWidth = layer.width();
    const auto layerHeight = layer.height();

    const auto tileWidth = tileset->tileWidth();
    const auto tileHeight = tileset->tileHeight();

    const auto surfaceWidth = layerWidth * tileset->tileWidth();
    const auto surfaceHeight = layerHeight * tileset->tileHeight();

    const auto sdlSurface = std::make_unique<SdlSurface>(surfaceWidth, surfaceHeight, 32);

    for (auto row = 0; row < layerHeight; ++row)
    {
        for (auto col = 0; col < layerWidth; ++col)
        {
            auto tileId = layer.tileId(col, row);

            if (0 >= tileId)
            {
                continue;
            }

            // Zero based gid on the tileset
            --tileId;

            const auto tilesetCol = tileId % (sdlTilesetSurfaceObject->w / tileWidth);
            const auto tilesetRow = tileId / (sdlTilesetSurfaceObject->h / tileHeight);

            SDL_Rect srcRect {};
            srcRect.x = tilesetCol * tileWidth;
            srcRect.y = tilesetRow * tileHeight;
            srcRect.w = tileWidth;
            srcRect.h = tileHeight;

            SDL_Rect dstRect {};
            dstRect.x = col * tileWidth;
            dstRect.y = row * tileHeight;
            dstRect.w = tileWidth;
            dstRect.h = tileHeight;

            SDL_BlitSurface(
                sdlTilesetSurfaceObject,
                &srcRect, sdlSurface->internalObject(),
                &dstRect
            );
        }
    }

    loadTextureFromSurface(renderer, *sdlSurface);
}

Texture::Impl::Impl(const Renderer& renderer, const TmxMap& map, const TmxObjectGroup& objectGroup,
                     const void *tilesetImageData, size_t tilesetImageDataSize)
{
    const auto objectCount = objectGroup.objectCount();

    auto minX = objectGroup.object(0)->x();
    auto minY = objectGroup.object(0)->y();
    auto maxX = minX;
    auto maxY = minY;
    for (auto i = 0; i < objectCount; ++i)
    {
        auto object = objectGroup.object(i);
        if (!object->hasGid())
        {
            continue;
        }

        int x = object->x();
        int y = object->y();

        minX = x < minX ? x : minX;
        minY = y < minY ? y : minY;
        maxX = x > maxX ? x : maxX;
        maxY = y > maxY ? y : maxY;
    }

    const auto tileset = map.tileset();

    const auto sdlRwops = std::make_unique<SdlRwops>(tilesetImageData, tilesetImageDataSize);
    const auto sdlTilesetSurface = std::make_unique<SdlSurface>(*sdlRwops);
    const auto sdlTilesetSurfaceObject = sdlTilesetSurface->internalObject();

    const auto tileWidth = tileset->tileWidth();
    const auto tileHeight = tileset->tileHeight();

    const auto surfaceWidth = tileWidth + maxX - minX;
    const auto surfaceHeight = tileHeight + maxY - minY;

    const auto sdlSurface = std::make_unique<SdlSurface>(surfaceWidth, surfaceHeight, 32);

    for (auto i = 0; i < objectCount; ++i)
    {
        const auto object = objectGroup.object(i);
        auto tileId = object->gid();

        if (tileId <= 0)
        {
            continue;
        }

        --tileId;

        const auto x = object->x() - minX;
        const auto y = object->y() - minY;

        const auto tilesetCol = tileId % (sdlTilesetSurfaceObject->w / tileWidth);
        const auto tilesetRow = tileId / (sdlTilesetSurfaceObject->h / tileHeight);

        SDL_Rect srcRect {};
        srcRect.x = tilesetCol * tileWidth;
        srcRect.y = tilesetRow * tileHeight;
        srcRect.w = tileWidth;
        srcRect.h = tileHeight;

        SDL_Rect dstRect {};
        dstRect.x = x;
        dstRect.y = y;
        dstRect.w = tileWidth;
        dstRect.h = tileHeight;

        SDL_BlitSurface(
            sdlTilesetSurfaceObject,
            &srcRect, sdlSurface->internalObject(),
            &dstRect
        );
    }

    loadTextureFromSurface(renderer, *sdlSurface);
}

Texture::Impl::Impl(const Renderer& renderer, const Font& font,
                     const std::string& text, Color32 foreground)
{
    const auto sdlSurface = std::make_unique<SdlSurface>(font, text, foreground);

    loadTextureFromSurface(renderer, *sdlSurface);
}

Texture::Impl::~Impl()
{
    SDL_DestroyTexture(m_texture);
}

int Texture::Impl::width() const
{
    return m_rect.w;
}

int Texture::Impl::height() const
{
    return m_rect.h;
}

SDL_Texture* Texture::Impl::internalObject() const
{
    return m_texture;
}

void Texture::Impl::loadTextureFromSurface(const Renderer& renderer, const SdlSurface& surface)
{
    const auto sdlRenderer = static_cast<SDL_Renderer*>(renderer.internalObject());

    m_texture = SDL_CreateTextureFromSurface(sdlRenderer, surface.internalObject());
    if (nullptr == m_texture)
    {
        throw std::runtime_error(SDL_GetError());
    }

    if (SDL_QueryTexture(m_texture, nullptr, nullptr, &m_rect.w, &m_rect.h) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
}
