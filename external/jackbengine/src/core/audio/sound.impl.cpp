//
// sound.impl.cpp
// jackbengine
//
// Created by Damien Bendejacq on 15/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include <string>
#include "sound.impl.hpp"
#include "core/sdl/io/sdlRwops.hpp"

using namespace Jackbengine;

Sound::Impl::Impl(const std::string& file)
{
    m_chunk = Mix_LoadWAV(file.c_str());
    if (nullptr == m_chunk)
    {
        throw std::runtime_error(Mix_GetError());
    }
}

Sound::Impl::Impl(const void *data, size_t dataSize)
{
    const auto sdlRwops = std::make_unique<SdlRwops>(data, dataSize);

    m_chunk = Mix_LoadWAV_RW(sdlRwops->internalObject(), 1);
    if (nullptr == m_chunk)
    {
        throw std::runtime_error(Mix_GetError());
    }
}

Sound::Impl::~Impl()
{
    Mix_FreeChunk(m_chunk);
}

void Sound::Impl::play(bool loop) const
{
    Mix_PlayChannel(MIX_DEFAULT_CHANNELS, m_chunk, loop ? 1 : 0);
}
