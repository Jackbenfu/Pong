//
// entityManager.hpp
// jackbengine
//
// Created by Damien Bendejacq on 20/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <map>
#include "entity.hpp"
#include "component/componentCollection.hpp"

namespace Jackbengine {

class EntityManager
{
    DISALLOW_COPY_AND_MOVE(EntityManager)

public:
    EntityManager() = default;
    ~EntityManager() = default;

    Entity addEntity();
    void removeEntity(Entity entity);
    bool isEntityEnabled(Entity entity) const;
    void enableEntity(Entity entity, bool enable);
    ComponentCollection& getEntity(Entity entity) const;

    template<typename TComponent, typename ...Args>
    void addComponent(Entity entity, Args&& ...args);

    template<typename TComponent>
    void removeComponent(Entity entity);

    template<typename TComponent>
    TComponent& getComponent(Entity entity) const;

    template<typename TComponent>
    void enableComponent(Entity entity, bool enable);

private:
    std::tuple<bool, std::unique_ptr<ComponentCollection>>& findEntity(Entity entity);
    const std::tuple<bool, std::unique_ptr<ComponentCollection>>& findEntity(Entity entity) const;

    template<typename T>
    static auto findEntity(T& t, Entity entity) -> decltype(t.findEntity(entity));

    std::map<Entity, std::tuple<bool, std::unique_ptr<ComponentCollection>>> m_entities;

};

template<typename TComponent, typename ...Args>
void EntityManager::addComponent(Entity entity, Args&& ...args)
{
    auto& tuple = findEntity(entity);

    std::get<1>(tuple)->add<TComponent>(std::forward<Args>(args)...);
}

template<typename TComponent>
void EntityManager::removeComponent(Entity entity)
{
    auto& tuple = findEntity(entity);

    std::get<1>(tuple)->remove<TComponent>();
}

template<typename TComponent>
TComponent& EntityManager::getComponent(Entity entity) const
{
    auto& tuple = findEntity(entity);
    auto& componentCollection = std::get<1>(tuple);

    return componentCollection->get<TComponent>();
}

template<typename TComponent>
void EntityManager::enableComponent(Entity entity, bool enable)
{
    auto& tuple = findEntity(entity);

    std::get<1>(tuple)->enable<TComponent>(enable);
}

template<typename T>
auto EntityManager::findEntity(T& t, Entity entity) -> decltype(t.findEntity(entity))
{
    auto it = t.m_entities.find(entity);
    if (it == t.m_entities.end())
    {
        throw std::runtime_error("Entity does not exist: " + std::to_string(entity));
    }

    return it->second;
}

} // namespace Jackbengine

#endif // __ENTITY_MANAGER_H__
