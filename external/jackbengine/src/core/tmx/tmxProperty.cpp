//
// tmxProperty.cpp
// jackbengine
//
// Created by Damien Bendejacq on 17/11/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "tmxProperty.hpp"

using namespace Jackbengine;

const char* TmxProperty::name() const
{
    return m_element->Attribute("name");
}

const char* TmxProperty::value() const
{
    return m_element->Attribute("value");
}

bool TmxProperty::intValue(int *value) const
{
    return 0 == m_element->QueryIntAttribute("value", value);
}

bool TmxProperty::unsignedIntValue(uint *value) const
{
    return 0 == m_element->QueryUnsignedAttribute("value", value);
}

bool TmxProperty::boolValue(bool *value) const
{
    return 0 == m_element->QueryBoolAttribute("value", value);
}

bool TmxProperty::doubleValue(double *value) const
{
    return 0 == m_element->QueryDoubleAttribute("value", value);
}

void TmxProperty::load(const TiXmlElement *element)
{
    m_element = element;
}
