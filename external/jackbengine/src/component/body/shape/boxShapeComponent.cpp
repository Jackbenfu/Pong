//
// boxShapeComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 28/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include <stdexcept>
#include "boxShapeComponent.hpp"

using namespace Jackbengine;

BoxShapeComponent::BoxShapeComponent(float width, float height)
    : m_vector {width, height}
{ }

float BoxShapeComponent::width() const
{
    return m_vector.x;
}

float BoxShapeComponent::height() const
{
    return m_vector.y;
}

const Vec2f& BoxShapeComponent::size() const
{
    return m_vector;
}

void BoxShapeComponent::setWidth(float width)
{
    if (width < 0.0f)
    {
        throw std::invalid_argument("width");
    }

    m_vector.x = width;
}

void BoxShapeComponent::setHeight(float height)
{
    if (height < 0.0f)
    {
        throw std::invalid_argument("height");
    }

    m_vector.y = height;
}

void BoxShapeComponent::setSize(float width, float height)
{
    setWidth(width);
    setHeight(height);
}
