//
// color32.hpp
// jackbengine
//
// Created by Damien Bendejacq on 18/06/15.
// Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __COLOR_H__
#define __COLOR_H__

#include "common.hpp"

namespace Jackbengine {

struct Color32
{
    Color32();
    Color32(byte r, byte g, byte b);
    Color32(byte r, byte g, byte b, byte a);

    byte r;
    byte g;
    byte b;
    byte a;
};

} // namespace Jackbengine

#endif // __COLOR_H__
