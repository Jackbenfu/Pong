//
// velocityComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "velocityComponent.hpp"

using namespace Jackbengine;

VelocityComponent::VelocityComponent(float x, float y)
    : m_velocity {x, y}
{ }

const Vec2f& VelocityComponent::get() const
{
    return m_velocity;
}

void VelocityComponent::set(float x, float y)
{
    m_velocity.x = x;
    m_velocity.y = y;
}

float VelocityComponent::x() const
{
    return m_velocity.x;
}

void VelocityComponent::setX(float x)
{
    m_velocity.x = x;
}

float VelocityComponent::y() const
{
    return m_velocity.y;
}

void VelocityComponent::setY(float y)
{
    m_velocity.y = y;
}
