//
// tmxObjectGroup.cpp
// jackbengine
//
// Created by Damien Bendejacq on 29/10/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "tmxObjectGroup.hpp"

using namespace Jackbengine;

TmxObjectGroup::TmxObjectGroup()
    : m_properties {std::unique_ptr<TmxPropertyGroup>(new TmxPropertyGroup())}
{ }

const char* TmxObjectGroup::name() const
{
    return m_name;
}

const TmxObject* TmxObjectGroup::object(int index) const
{
    if (0 <= index && static_cast<int>(m_objects.size()) > index)
    {
        return m_objects[index].get();
    }

    return nullptr;
}

const TmxObject* TmxObjectGroup::object(const char *name) const
{
    for (auto& object : m_objects)
    {
        if (0 == strcmp(name, object->name()))
        {
            return object.get();
        }
    }

    return nullptr;
}

int TmxObjectGroup::objectCount() const
{
    return static_cast<int>(m_objects.size());
}

int TmxObjectGroup::originX() const
{
    auto originX = 0;

    for (auto& object : m_objects)
    {
        auto objectX = object->x();

        originX = objectX < originX ? objectX : originX;
    }

    return originX;
}

int TmxObjectGroup::originY() const
{
    auto originY = 0;

    for (auto& object : m_objects)
    {
        auto objectY = object->y();

        originY = objectY < originY ? objectY : originY;
    }

    return originY;
}

bool TmxObjectGroup::hasProperty(const char *name) const
{
    if (nullptr == m_properties)
    {
        return false;
    }

    return m_properties->hasProperty(name);
}

const TmxPropertyGroup* TmxObjectGroup::properties() const
{
    return m_properties.get();
}

void TmxObjectGroup::load(const TiXmlElement *element)
{
    m_name = element->Attribute("name");

    auto node = element->FirstChild();
    while (nullptr != node)
    {
        if (0 == strcmp("object", node->Value()))
        {
            auto object = std::unique_ptr<TmxObject>(new TmxObject());
            object->load(node->ToElement());
            m_objects.push_back(std::move(object));
        }
        else if (0 == strcmp("properties", node->Value()))
        {
            m_properties->load(node->ToElement());
        }

        node = node->NextSibling();
    }
}
