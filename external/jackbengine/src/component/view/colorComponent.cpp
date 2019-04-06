//
// colorComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 01/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "colorComponent.hpp"

using namespace Jackbengine;

ColorComponent::ColorComponent(Color32 color)
    : ColorComponent(color.r, color.g, color.b, color.a)
{ }

ColorComponent::ColorComponent(byte red, byte green, byte blue, byte alpha)
    : m_color {red, green, blue, alpha}
{ }

ColorComponent::ColorComponent(byte red, byte green, byte blue)
    : m_color {red, green, blue}
{ }

Color32 ColorComponent::getColor() const
{
    return m_color;
}

byte ColorComponent::red() const
{
    return m_color.r;
}

void ColorComponent::setRed(byte value)
{
    m_color.r = value;
}

byte ColorComponent::green() const
{
    return m_color.g;
}

void ColorComponent::setGreen(byte value)
{
    m_color.g = value;
}

byte ColorComponent::blue() const
{
    return m_color.b;
}

void ColorComponent::setBlue(byte value)
{
    m_color.b = value;
}

byte ColorComponent::alpha() const
{
    return m_color.a;
}

void ColorComponent::setAlpha(byte value)
{
    m_color.a = value;
}
