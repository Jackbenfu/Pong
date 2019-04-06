//
// platform.hpp
// jackbengine
//
// Created by Damien Bendejacq on 26/05/2016.
// Copyright © 2016 Damien Bendejacq. All rights reserved.
//

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

// Platform specific includes
#if defined(__APPLE__)
    #include "core/platform/osx.hpp"
#elif defined(_WIN32)
    #include "core/platform/win32.hpp"
#elif defined(EMSCRIPTEN)
    #include "core/platform/emscripten.hpp"
#endif

#endif // __PLATFORM_H__
