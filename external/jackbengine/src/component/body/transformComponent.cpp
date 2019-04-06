//
// transformComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 29/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "transformComponent.hpp"

using namespace Jackbengine;

TransformComponent::TransformComponent(float positionX, float positionY)
    : TransformComponent {positionX, positionY, 1.0f, 1.0f, 0.0}
{ }

TransformComponent::TransformComponent(float positionX, float positionY, double angle)
    : TransformComponent {positionX, positionY, 1.0f, 1.0f, angle}
{ }

TransformComponent::TransformComponent(float positionX, float positionY, float scaleX, float scaleY)
    : TransformComponent {positionX, positionY, scaleX, scaleY, 0.0}
{ }

TransformComponent::TransformComponent(
    float positionX, float positionY, float scaleX, float scaleY, double angle)
    : m_position {positionX, positionY},
      m_scale {scaleX, scaleY},
      m_angle {angle}
{ }

const Vec2f& TransformComponent::position() const
{
    return m_position;
}

float TransformComponent::positionX() const
{
    return m_position.x;
}

float TransformComponent::positionY() const
{
    return m_position.y;
}

void TransformComponent::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
}

void TransformComponent::setPositionX(float x)
{
    m_position.x = x;
}

void TransformComponent::setPositionY(float y)
{
    m_position.y = y;
}

double TransformComponent::angle() const
{
    return m_angle;
}

void TransformComponent::setAngle(double angle)
{
    m_angle = angle;
}

const Vec2f& TransformComponent::scale() const
{
    return m_scale;
}

float TransformComponent::scaleX() const
{
    return m_scale.x;
}

float TransformComponent::scaleY() const
{
    return m_scale.y;
}

void TransformComponent::setScale(float x, float y)
{
    m_scale.x = x;
    m_scale.y = y;
}

void TransformComponent::setScaleX(float x)
{
    m_scale.x = x;
}

void TransformComponent::setScaleY(float y)
{
    m_scale.y = y;
}
