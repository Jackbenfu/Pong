//
// aabbCollisionSystem.cpp
// jackbengine
//
// Created by Damien Bendejacq on 20/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include <limits>
#include <algorithm>
#include "aabbCollisionSystem.hpp"
#include "component/body/shape/boxShapeComponent.hpp"
#include "component/body/transformComponent.hpp"
#include "component/body/velocityComponent.hpp"
#include "component/misc/tagComponent.hpp"

using namespace Jackbengine;

int AABBCollisionSystem::order() const
{
    return (int)SystemOrder::AABBCollision;
}

void AABBCollisionSystem::frame(float delta)
{
    for (auto group : m_groups)
    {
        auto ltag1 = group.first;
        auto ltag2 = group.second;

        for (auto entity1 : m_entities)
        {
            auto components1 = entity1.second;

            auto& tag1 = components1->get<Tag>();
            if (tag1.get() == ltag1)
            {
                for (auto entity2 : m_entities)
                {
                    if (entity1.first == entity2.first)
                    {
                        continue;
                    }

                    auto components2 = entity2.second;

                    auto& tag2 = components2->get<Tag>();
                    if (tag2.get() == ltag2)
                    {
                        testCollision(delta, *components1, *components2);
                    }
                }
            }
        }
    }
}

bool AABBCollisionSystem::hasRequiredComponents(ComponentCollection& components) const
{
    return components.any<BoxShape>()
        && components.any<Tag>()
        && components.any<Transform>()
        && components.any<Velocity>();
}

void AABBCollisionSystem::addGroup(const std::string& tag1, const std::string& tag2)
{
    const auto predicate = [&](const auto& pair)
    {
        return pair.first == tag1 && pair.second == tag2;
    };

    if (std::any_of(m_groups.begin(), m_groups.end(), predicate))
    {
        throw std::runtime_error("Collision group already exists: (" + tag1 + "," + tag2 + ")");
    }

    m_groups.emplace_back(tag1, tag2);
}

void AABBCollisionSystem::removeGroup(const std::string& tag1, const std::string& tag2)
{
    const auto predicate = [&](const auto& pair)
    {
        return pair.first == tag1 && pair.second == tag2;
    };

    auto it = std::find_if(m_groups.begin(), m_groups.end(), predicate);

    if (it == m_groups.end())
    {
        throw std::runtime_error("Collision group does not exist: (" + tag1 + "," + tag2 + ")");
    }

    m_groups.erase(it);
}

void AABBCollisionSystem::setCallback(AABBCollisionCallback callback)
{
    m_callback = callback;
}

void AABBCollisionSystem::unsetCallback()
{
    m_callback = nullptr;
}

void AABBCollisionSystem::testCollision(float delta, ComponentCollection& components1, ComponentCollection& components2) const
{
    auto& transform1 = components1.get<Transform>();
    auto x1 = transform1.positionX();
    auto y1 = transform1.positionY();

    auto& boxShape1 = components1.get<BoxShape>();
    auto w1 = boxShape1.width();
    auto h1 = boxShape1.height();

    auto& transform2 = components2.get<Transform>();
    auto x2 = transform2.positionX();
    auto y2 = transform2.positionY();

    auto& boxShape2 = components2.get<BoxShape>();
    auto w2 = boxShape2.width();
    auto h2 = boxShape2.height();

    if (!(x1 >= x2 + w2 || x1 + w1 <= x2 || y1 >= y2 + h2 || y1 + h1 <= y2))
    {
        auto& velocity1 = components1.get<Velocity>();
        auto vX1 = velocity1.x();
        auto vY1 = velocity1.y();

        // Required move to go back to the position just before the collision
        auto xToCollision = vX1 > 0.0f ? x2 - (x1 + w1) : (x2 + w2) - x1;
        auto yToCollision = vY1 > 0.0f ? y2 - (y1 + h1) : (y2 + h2) - y1;

        // Same as above expressed in percentage (value from 0 to 1)
        auto xOffsetToCollision = 0.0f == vX1
                                  ? -std::numeric_limits<float>::infinity()
                                  : xToCollision / vX1;

        auto yOffsetToCollision = 0.0f == vY1
                                  ? -std::numeric_limits<float>::infinity()
                                  : yToCollision / vY1;

        // Collision time is the latest among the two axes
        auto collisionTime = std::max(xOffsetToCollision, yOffsetToCollision);

        // Collision normals to find on which AABB side the collision occured
        float normalX;
        float normalY;
        AABBCollisionSide collisionSide;
        if (xOffsetToCollision > yOffsetToCollision)
        {
            normalX = xToCollision < 0.0f ? -1.0f : 1.0f;
            normalY = 0.0f;

            collisionSide = -1.0f == normalX ? AABBCollisionSide::Left : AABBCollisionSide::Right;
        }
        else
        {
            normalY = yToCollision < 0.0f ? -1.0f : 1.0f;
            normalX = 0.0f;

            collisionSide = -1.0f == normalY ? AABBCollisionSide::Top : AABBCollisionSide::Bottom;
        }

        // Position where the collision occured
        auto xCollision = x1 + vX1 * collisionTime;
        auto yCollision = y1 + vY1 * collisionTime;

        // Setting new position
        transform1.setPosition(xCollision, yCollision);

        auto collisionResolved = false;
        if (nullptr != m_callback)
        {
            // If a callback is defined, we let the developer
            // choose the collision response behavior
            collisionResolved = m_callback(delta, components1, components2, collisionSide);
        }

        // Default behavior if collision not resolved by user
        if (!collisionResolved)
        {
            // Setting new velocity for "bounce" effect
            if (0.0f != normalX)
            {
                velocity1.setX(-vX1);
            }

            if (0.0f != normalY)
            {
                velocity1.setY(-vY1);
            }
        }
    }
}
