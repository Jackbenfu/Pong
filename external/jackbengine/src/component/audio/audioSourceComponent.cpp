//
// audioSourceComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 21/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "audioSourceComponent.hpp"

using namespace Jackbengine;

AudioSourceComponent::AudioSourceComponent(const std::string& file)
    : m_sound {file}
{ }

AudioSourceComponent::AudioSourceComponent(const void *data, size_t dataSize)
    : m_sound {data, dataSize}
{ }

void AudioSourceComponent::play() const
{
    m_sound.play(false);
}

void AudioSourceComponent::play(bool loop) const
{
    m_sound.play(loop);
}
