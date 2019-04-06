//
// sound.hpp
// jackbengine
//
// Created by Damien Bendejacq on 15/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SOUND_H__
#define __SOUND_H__

#include <memory>
#include "common.hpp"

namespace Jackbengine {

class Sound
{
    DISALLOW_COPY_AND_MOVE(Sound)

public:
    explicit Sound(const std::string& file);
    Sound(const void *data, size_t dataSize);

    ~Sound();

    void play(bool loop) const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace Jackbengine

#endif // __SOUND_H__
