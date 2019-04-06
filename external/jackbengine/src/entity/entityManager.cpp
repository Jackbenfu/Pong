//
// entityManager.cpp
// jackbengine
//
// Created by Damien Bendejacq on 20/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "entityManager.hpp"

using namespace Jackbengine;

Entity EntityManager::addEntity()
{
    static size_t entityCounter = 0;

    m_entities[++entityCounter] = std::make_tuple(
        true,
        std::make_unique<ComponentCollection>()
    );

    return entityCounter;
}

void EntityManager::removeEntity(Entity entity)
{
    m_entities.erase(entity);
}

bool EntityManager::isEntityEnabled(Entity entity) const
{
    return std::get<0>(findEntity(entity));
}

void EntityManager::enableEntity(Entity entity, bool enable)
{
    std::get<0>(findEntity(entity)) = enable;
}

ComponentCollection& EntityManager::getEntity(Entity entity) const
{
    return *std::get<1>(findEntity(entity));
}

std::tuple<bool, std::unique_ptr<ComponentCollection>>& EntityManager::findEntity(Entity entity)
{
    return findEntity(*this, entity);
}

const std::tuple<bool, std::unique_ptr<ComponentCollection>>& EntityManager::findEntity(Entity entity) const
{
    return findEntity(*this, entity);
}
