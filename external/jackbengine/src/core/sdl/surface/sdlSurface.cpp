//
// sdlSurface.cpp
// jackbengine
//
// Created by Damien Bendejacq on 15/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "sdlSurface.hpp"

using namespace Jackbengine;

SdlSurface::SdlSurface(const std::string& file)
{
    m_surface = IMG_Load(file.c_str());
    if (nullptr == m_surface)
    {
        throw std::runtime_error(IMG_GetError());
    }
}

SdlSurface::SdlSurface(const SdlRwops& rwops)
{
    m_surface = IMG_Load_RW(rwops.internalObject(), 0);
    if (nullptr == m_surface)
    {
        throw std::runtime_error(IMG_GetError());
    }
}

SdlSurface::SdlSurface(int width, int height, int depth)
{
    m_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, depth, 0, 0, 0, 0);
    if (nullptr == m_surface)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

SdlSurface::SdlSurface(const Font& font, const std::string& text, Color32 foreground)
{
    const auto sdlFont = static_cast<TTF_Font*>(font.internalObject());

    SDL_Color sdlForeground {foreground.r, foreground.g, foreground.b, foreground.a};

    m_surface = TTF_RenderUTF8_Solid(sdlFont, text.c_str(), sdlForeground);
    if (nullptr == m_surface)
    {
        throw std::runtime_error(TTF_GetError());
    }
}

SdlSurface::~SdlSurface()
{
    SDL_FreeSurface(m_surface);
}

SDL_Surface* SdlSurface::internalObject() const
{
    return m_surface;
}
