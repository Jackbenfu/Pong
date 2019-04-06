//
// tmxPropertyGroup.cpp
// jackbengine
//
// Created by Damien Bendejacq on 17/11/14.
// Copyright © 2014 Damien Bendejacq. All rights reserved.
//

#include "tmxPropertyGroup.hpp"

using namespace std;
using namespace Jackbengine;

bool TmxPropertyGroup::hasProperty(const char *name) const
{
    return nullptr != rawProperty(name);
}

const char* TmxPropertyGroup::property(const char *name) const
{
    auto property = rawProperty(name);
    if (nullptr != property)
    {
        return property->value();
    }

    return nullptr;
}

bool TmxPropertyGroup::intProperty(const char *name, int *value) const
{
    auto property = rawProperty(name);
    if (nullptr != property)
    {
        return property->intValue(value);
    }

    return false;
}

bool TmxPropertyGroup::unsignedIntProperty(const char *name, uint *value) const
{
    auto property = rawProperty(name);
    if (nullptr != property)
    {
        return property->unsignedIntValue(value);
    }

    return false;
}

bool TmxPropertyGroup::boolProperty(const char *name, bool *value) const
{
    auto property = rawProperty(name);
    if (nullptr != property)
    {
        return property->boolValue(value);
    }

    return false;
}

bool TmxPropertyGroup::doubleProperty(const char *name, double *value) const
{
    auto property = rawProperty(name);
    if (nullptr != property)
    {
        return property->doubleValue(value);
    }

    return false;
}

const TmxProperty* TmxPropertyGroup::rawProperty(const char *name) const
{
    auto it = m_properties.begin();
    while (m_properties.end() != it)
    {
        auto property = (*it).get();
        if (nullptr != property && 0 == strcmp(property->name(), name))
        {
            return property;
        }

        ++it;
    }

    return nullptr;
}

void TmxPropertyGroup::load(const TiXmlElement *element)
{
    auto node = element->FirstChild();
    while (nullptr != node)
    {
        if (0 == strcmp("property", node->Value()))
        {
            auto property = std::unique_ptr<TmxProperty>(new TmxProperty());
            property->load(node->ToElement());
            m_properties.push_back(std::move(property));
        }

        node = node->NextSibling();
    }
}
