//
// window.hpp
// jackbengine
//
// Created by Damien Bendejacq on 11/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <memory>
#include <string>
#include "common.hpp"

namespace Jackbengine {

class Window
{
    friend class Renderer;

    DISALLOW_COPY_AND_MOVE(Window)

public:
    Window(const std::string& title, int width, int height, bool fullscreen);
    ~Window();

    int width() const;
    int height() const;

private:
    void* internalObject() const;

    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace Jackbengine

#endif // __WINDOW_H__
