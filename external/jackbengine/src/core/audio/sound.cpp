//
// sound.cpp
// jackbengine
//
// Created by Damien Bendejacq on 15/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "sound.hpp"
#include "sound.impl.hpp"

using namespace Jackbengine;

Sound::Sound(const std::string& file)
    : m_impl {std::make_unique<Impl>(file)}
{ }

Sound::Sound(const void *data, size_t dataSize)
    : m_impl {std::make_unique<Impl>(data, dataSize)}
{ }

Sound::~Sound() = default;

void Sound::play(bool loop) const
{
    m_impl->play(loop);
}
