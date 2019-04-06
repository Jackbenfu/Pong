//
// input.cpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "input.hpp"
#include "input.impl.hpp"

using namespace Jackbengine;

Input::Input()
    : m_impl {std::make_unique<Impl>()}
{ }

Input::~Input() = default;

void Input::update()
{
    m_impl->update();
}

bool Input::keyDown(KeyboardKey key) const
{
    return m_impl->keyDown(key);
}

bool Input::keyUp(KeyboardKey key) const
{
    return m_impl->keyUp(key);
}

bool Input::keyPress(KeyboardKey key) const
{
    return m_impl->keyPress(key);
}

bool Input::mouseDown(MouseButton button) const
{
    return m_impl->mouseDown(button);
}

bool Input::mouseUp(MouseButton button) const
{
    return m_impl->mouseUp(button);
}

bool Input::mouseClick(MouseButton button) const
{
    return m_impl->mouseClick(button);
}

bool Input::mouseMove() const
{
    return m_impl->mouseMove();
}

const Jackbengine::Vector2d<int>& Input::mousePosition() const
{
    return m_impl->mousePosition();
}

bool Input::quit() const
{
    return m_impl->quit();
}
