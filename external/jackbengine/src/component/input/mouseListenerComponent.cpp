//
// mouseListenerComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 07/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "mouseListenerComponent.hpp"

using namespace Jackbengine;

void MouseListenerComponent::onLeftClick(MouseCallback callback)
{
    m_onLeftClick = std::move(callback);
}

void MouseListenerComponent::callLeftClick()
{
    addEvent(MouseEvent::MouseEvent_LeftClick);
    if (nullptr != m_onLeftClick)
    {
        m_onLeftClick();
    }
}

void MouseListenerComponent::onLeftDown(MouseCallback callback)
{
    m_onLeftDown = std::move(callback);
}

void MouseListenerComponent::callLeftDown() const
{
    if (nullptr != m_onLeftDown)
    {
        m_onLeftDown();
    }
}

void MouseListenerComponent::onMiddleClick(MouseCallback callback)
{
    m_onMiddleClick = std::move(callback);
}

void MouseListenerComponent::callMiddleClick()
{
    addEvent(MouseEvent::MouseEvent_MiddleClick);
    if (nullptr != m_onMiddleClick)
    {
        m_onMiddleClick();
    }
}

void MouseListenerComponent::onMiddleDown(MouseCallback callback)
{
    m_onMiddleDown = std::move(callback);
}

void MouseListenerComponent::callMiddleDown() const
{
    if (nullptr != m_onMiddleDown)
    {
        m_onMiddleDown();
    }
}

void MouseListenerComponent::onRightClick(MouseCallback callback)
{
    m_onRightClick = std::move(callback);
}

void MouseListenerComponent::callRightClick()
{
    addEvent(MouseEvent::MouseEvent_RightClick);
    if (nullptr != m_onRightClick)
    {
        m_onRightClick();
    }
}

void MouseListenerComponent::onRightDown(MouseCallback callback)
{
    m_onRightDown = std::move(callback);
}

void MouseListenerComponent::callRightDown() const
{
    if (nullptr != m_onRightDown)
    {
        m_onRightDown();
    }
}

void MouseListenerComponent::onHover(MouseCallback callback)
{
    m_onHover = std::move(callback);
}

void MouseListenerComponent::callOnHover()
{
    addEvent(MouseEvent::MouseEvent_Hover);
    if (nullptr != m_onHover)
    {
        m_onHover();
    }
}

void MouseListenerComponent::onEnter(MouseCallback callback)
{
    m_onEnter = std::move(callback);
}

void MouseListenerComponent::callOnEnter()
{
    addEvent(MouseEvent::MouseEvent_Enter);
    if (nullptr != m_onEnter)
    {
        m_onEnter();
    }
}

void MouseListenerComponent::onExit(MouseCallback callback)
{
    m_onExit = std::move(callback);
}

void MouseListenerComponent::callOnExit()
{
    addEvent(MouseEvent::MouseEvent_Exit);
    if (nullptr != m_onExit)
    {
        m_onExit();
    }
}

bool MouseListenerComponent::leftClick()
{
    return hasAndRemoveEvent(MouseEvent::MouseEvent_LeftClick);
}

bool MouseListenerComponent::middleClick()
{
    return hasAndRemoveEvent(MouseEvent::MouseEvent_MiddleClick);
}

bool MouseListenerComponent::rightClick()
{
    return hasAndRemoveEvent(MouseEvent::MouseEvent_RightClick);
}

bool MouseListenerComponent::hover() const
{
    return hasEvent(MouseEvent::MouseEvent_Hover);
}

bool MouseListenerComponent::enter() const
{
    return hasEvent(MouseEvent::MouseEvent_Enter);
}

bool MouseListenerComponent::exit() const
{
    return hasEvent(MouseEvent::MouseEvent_Exit);
}

void MouseListenerComponent::addEvent(MouseEvent event)
{
    m_events |= event;
}

void MouseListenerComponent::removeEvent(MouseEvent event)
{
    m_events &= ~event;
}

bool MouseListenerComponent::hasAndRemoveEvent(MouseEvent event)
{
    bool result = hasEvent(event);
    removeEvent(event);

    return result;
}

bool MouseListenerComponent::hasEvent(MouseEvent event) const
{
    return event == (m_events & event);
}
