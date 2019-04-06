//
// system.hpp
// jackbengine
//
// Created by Damien Bendejacq on 25/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <map>
#include "core/collection/orderableItem.hpp"
#include "entity/entityManager.hpp"
#include "systemOrder.hpp"

namespace Jackbengine {

class System : public OrderableItem
{
    friend class SystemManager;

    DISALLOW_COPY_AND_MOVE(System)

public:
    System() = default;
    virtual ~System() = default;

protected:
    std::map<Entity, ComponentCollection*> m_entities;

private:
    virtual void frame(float delta) = 0;
    virtual bool hasRequiredComponents(ComponentCollection& components) const = 0;

    void addEntity(Entity entity, ComponentCollection& components);
    void removeEntity(Entity entity, bool checkComponents);
};

} // namespace Jackbengine

#endif // __SYSTEM_H__
