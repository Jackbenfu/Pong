//
// motionSystem.cpp
// jackbengine
//
// Created by Damien Bendejacq on 09/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "motionSystem.hpp"
#include "component/body/transformComponent.hpp"
#include "component/body/velocityComponent.hpp"

using namespace Jackbengine;

int MotionSystem::order() const
{
    return (int)SystemOrder::Motion;
}

void MotionSystem::frame(float delta)
{
    for (const auto& entity : m_entities)
    {
        const auto components = entity.second;

        auto& transform = components->get<TransformComponent>();
        const auto& velocity = components->get<VelocityComponent>();

        const auto velocityVec = velocity.get();
        if (velocityVec.isZero())
        {
            continue;
        }

        const auto positionVec = transform.position();

        transform.setPosition(
            positionVec.x + velocityVec.x * delta,
            positionVec.y + velocityVec.y * delta
        );
    }
}

bool MotionSystem::hasRequiredComponents(ComponentCollection& components) const
{
    return components.any<TransformComponent>()
        && components.any<VelocityComponent>();
}
