//
// sdlRwops.hpp
// jackbengine
//
// Created by Damien Bendejacq on 15/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SDL_RWOPS_H__
#define __SDL_RWOPS_H__

#include "common.hpp"
#include "platform.hpp"

namespace Jackbengine {

class SdlRwops
{
    DISALLOW_COPY_AND_MOVE(SdlRwops)

public:
    SdlRwops(const void *data, size_t dataSize);
    ~SdlRwops() = default;

    SDL_RWops* internalObject() const;

private:
    SDL_RWops *m_rwops {nullptr};
};

} // namespace Jackbengine

#endif // __SDL_RWOPS_H__
