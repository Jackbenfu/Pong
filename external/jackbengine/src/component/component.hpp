//
// component.hpp
// jackbengine
//
// Created by Damien Bendejacq on 21/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "common.hpp"

namespace Jackbengine {

class Component
{
    DISALLOW_COPY_AND_MOVE(Component)

public:
    Component() = default;
    virtual ~Component() = default;
};

} // namespace Jackbengine

#endif // __COMPONENT_H__
