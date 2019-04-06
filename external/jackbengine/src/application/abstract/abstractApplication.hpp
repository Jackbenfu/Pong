//
// abstractApplication.hpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __ABSTRACT_APPLICATION_H__
#define __ABSTRACT_APPLICATION_H__

#include "common.hpp"

namespace Jackbengine {

class AbstractApplication
{
    DISALLOW_COPY_AND_MOVE(AbstractApplication)

public:
    AbstractApplication();
    virtual ~AbstractApplication();
};

} // namespace Jackbengine

#endif // __ABSTRACT_APPLICATION_H__
