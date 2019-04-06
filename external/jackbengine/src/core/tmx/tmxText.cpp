//
// tmxText.cpp
// jackbengine
//
// Created by Damien Bendejacq on 04/10/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "tmxText.hpp"

using namespace Jackbengine;

int TmxText::pixelsize() const
{
    return m_pixelsize;
}

const char* TmxText::color() const
{
    return m_color;
}

const char* TmxText::halign() const
{
    return m_halign;
}

const char* TmxText::valign() const
{
    return m_valign;
}

const char* TmxText::text() const
{
    return m_text;
}

void TmxText::load(const TiXmlElement *element)
{
    element->Attribute("pixelsize", &m_pixelsize);
    m_color = element->Attribute("color");
    m_halign = element->Attribute("halign");
    m_valign = element->Attribute("valign");
    m_text = element->GetText();
}
