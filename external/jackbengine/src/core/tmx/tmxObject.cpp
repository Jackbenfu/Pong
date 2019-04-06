//
// tmxObject.cpp
// jackbengine
//
// Created by Damien Bendejacq on 29/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "tmxObject.hpp"

using namespace Jackbengine;

const char* TmxObject::name() const
{
    return m_name;
}

int TmxObject::gid() const
{
    return m_gid;
}

bool TmxObject::hasGid() const
{
    return m_gid > 0;
}

int TmxObject::x() const
{
    return m_x;
}

int TmxObject::y() const
{
    return m_y;
}

int TmxObject::width() const
{
    return m_width;
}

int TmxObject::height() const
{
    return m_height;
}

const char* TmxObject::type() const
{
    return m_type;
}

bool TmxObject::hasProperty(const char *name) const
{
    if (nullptr == m_properties)
    {
        return false;
    }

    return m_properties->hasProperty(name);
}

const TmxPropertyGroup* TmxObject::properties() const
{
    return m_properties.get();
}

bool TmxObject::hasText() const
{
    return m_text != nullptr;
}

const TmxText* TmxObject::text() const
{
    return m_text.get();
}

void TmxObject::load(const TiXmlElement *element)
{
    m_name = element->Attribute("name");
    m_type = element->Attribute("type");
    element->Attribute("gid", &m_gid);
    element->Attribute("x", &m_x);
    element->Attribute("y", &m_y);
    element->Attribute("width", &m_width);
    element->Attribute("height", &m_height);

    auto node = element->FirstChild();
    while (nullptr != node)
    {
        if (0 == strcmp("properties", node->Value()))
        {
            m_properties = std::unique_ptr<TmxPropertyGroup>(new TmxPropertyGroup());
            m_properties->load(node->ToElement());
        }

        if (0 == strcmp("text", node->Value()))
        {
            m_text = std::unique_ptr<TmxText>(new TmxText());
            m_text->load(node->ToElement());
        }

        node = node->NextSibling();
    }
}
