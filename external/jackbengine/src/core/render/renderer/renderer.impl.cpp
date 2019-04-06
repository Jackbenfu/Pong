//
// renderer.impl.cpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "renderer.impl.hpp"
#include "core/render/texture/texture.hpp"

using namespace Jackbengine;

Renderer::Impl::Impl(const Window& window)
{
    const auto sdlWindow = static_cast<SDL_Window*>(window.internalObject());

    m_renderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (nullptr == m_renderer)
    {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_GetWindowSize(sdlWindow, &m_width, &m_height);
}

Renderer::Impl::~Impl()
{
    SDL_DestroyRenderer(m_renderer);
}

void Renderer::Impl::clear()
{
    setRenderColor(m_clearColor);

    if (SDL_RenderClear(m_renderer) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

void Renderer::Impl::present()
{
    SDL_RenderPresent(m_renderer);
}

void Renderer::Impl::setClearColor(Color32 color)
{
    m_clearColor = color;
}

void Renderer::Impl::setRenderColor(Color32 color)
{
    if (SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

void Renderer::Impl::renderTexture(int x, int y, const Texture& texture)
{
    renderTexture(x, y, texture, 0.0);
}

void Renderer::Impl::renderTexture(int x, int y, const Texture& texture, double angle)
{
    const auto sdlTexture = static_cast<SDL_Texture*>(texture.internalObject());

    SDL_Rect rect {};
    rect.x = x;
    rect.y = y;
    rect.w = texture.width();
    rect.h = texture.height();

    SDL_RenderCopyEx(m_renderer, sdlTexture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE);
}

void Renderer::Impl::renderLine(float x1, float y1, float x2, float y2, Color32 color)
{
    setRenderColor(color);

    if (SDL_RenderDrawLine(m_renderer, (int)x1, (int)y1, (int)x2, (int)y2) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

void Renderer::Impl::renderPoint(float x, float y, Color32 color)
{
    setRenderColor(color);

    if (SDL_RenderDrawPoint(m_renderer, (int)x, (int)y) < 0)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

int Renderer::Impl::width() const
{
    return m_width;
}

int Renderer::Impl::height() const
{
    return m_height;
}

SDL_Renderer* Renderer::Impl::internalObject() const
{
    return m_renderer;
}
