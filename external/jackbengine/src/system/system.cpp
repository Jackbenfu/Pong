//
// system.cpp
// jackbengine
//
// Created by Damien Bendejacq on 25/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "system.hpp"

using namespace Jackbengine;

void System::addEntity(Entity entity, ComponentCollection& components)
{
    if (!hasRequiredComponents(components))
    {
        return;
    }

    m_entities[entity] = &components;
}

void System::removeEntity(Entity entity, bool checkComponents)
{
    if (!checkComponents)
    {
        m_entities.erase(entity);
    }

    const auto it = m_entities.find(entity);
    if (it == m_entities.end())
    {
        return;
    }

    if (hasRequiredComponents(*it->second))
    {
        return;
    }

    m_entities.erase(entity);
}
