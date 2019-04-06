//
// systemManager.cpp
// jackbengine
//
// Created by Damien Bendejacq on 25/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "systemManager.hpp"

using namespace Jackbengine;

SystemManager::SystemManager(const EntityManager& entityManager)
    : m_entityManager {entityManager}
{ }

void SystemManager::addEntity(Entity entity)
{
    auto& components = m_entityManager.getEntity(entity);

    const auto lambda = [&](System& system)
    {
        system.addEntity(entity, components);
    };

    m_systems.apply(lambda);
}

void SystemManager::removeEntity(Entity entity, bool checkComponents)
{
    const auto lambda = [&](System& system)
    {
        system.removeEntity(entity, checkComponents);
    };

    m_systems.apply(lambda);
}

void SystemManager::frame(float delta)
{
    const auto lambda = [&delta](System& system)
    {
        system.frame(delta);
    };

    m_systems.apply(lambda);
}
