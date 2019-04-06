//
// containerComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "containerComponent.hpp"

using namespace Jackbengine;

ContainerComponent::ContainerComponent(int x, int y, int w, int h)
    : m_rect {x, y, w, h}
{ }

const Recti& ContainerComponent::rect() const
{
    return m_rect;
}

void ContainerComponent::setRect(int x, int y, int w, int h)
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = w;
    m_rect.h = h;
}

bool ContainerComponent::contains(float x, float y) const
{
    return x >= m_rect.x &&
           x <= m_rect.x + m_rect.w &&
           y >= m_rect.y &&
           y <= m_rect.y + m_rect.h;
}

bool ContainerComponent::contains(const Vec2i& point) const
{
    return contains((float)point.x, (float)point.y);
}

bool ContainerComponent::contains(const Vec2f& point) const
{
    return contains(point.x, point.y);
}

int ContainerComponent::x() const
{
    return m_rect.x;
}

int ContainerComponent::y() const
{
    return m_rect.y;
}

int ContainerComponent::width() const
{
    return m_rect.w;
}

int ContainerComponent::height() const
{
    return m_rect.h;
}
