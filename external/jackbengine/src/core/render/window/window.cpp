//
// window.cpp
// jackbengine
//
// Created by Damien Bendejacq on 11/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "window.hpp"
#include "window.impl.hpp"

using namespace Jackbengine;

Window::Window(const std::string& title, int width, int height, bool fullscreen)
    : m_impl {std::make_unique<Impl>(title, width, height, fullscreen)}
{ }

Window::~Window() = default;

int Window::width() const
{
    return m_impl->width();
}

int Window::height() const
{
    return m_impl->height();
}

void* Window::internalObject() const
{
    return m_impl->internalObject();
}
