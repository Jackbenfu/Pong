//
// tmxImage.cpp
// jackbengine
//
// Created by Damien Bendejacq on 28/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "tmxImage.hpp"

using namespace Jackbengine;

const char* TmxImage::source() const
{
    return m_source;
}

int TmxImage::width() const
{
    return m_width;
}

int TmxImage::height() const
{
    return m_height;
}

void TmxImage::load(const TiXmlElement *element)
{
    m_source = element->Attribute("source");
    element->Attribute("width", &m_width);
    element->Attribute("height", &m_height);
}
