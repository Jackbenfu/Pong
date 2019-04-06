//
// aabbCollisionSystem.hpp
// jackbengine
//
// Created by Damien Bendejacq on 20/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __AABB_COLLISION_SYSTEM_H__
#define __AABB_COLLISION_SYSTEM_H__

#include <vector>
#include <string>
#include "system/system.hpp"

namespace Jackbengine {

enum class AABBCollisionSide
{
    Top,
    Right,
    Bottom,
    Left,
};

using AABBCollisionCallback =
    std::function<bool(
        float,
        ComponentCollection&,
        ComponentCollection&,
        AABBCollisionSide
    )>;

class AABBCollisionSystem final : public System
{
    DISALLOW_COPY_AND_MOVE(AABBCollisionSystem)

public:
    AABBCollisionSystem() = default;
    ~AABBCollisionSystem() override = default;

    int order() const final;

    void addGroup(const std::string& tag1, const std::string& tag2);
    void removeGroup(const std::string& tag1, const std::string& tag2);

    void setCallback(AABBCollisionCallback callback);
    void unsetCallback();

private:
    void frame(float delta) override;
    bool hasRequiredComponents(ComponentCollection& components) const override;

    void testCollision(float delta, ComponentCollection& components1, ComponentCollection& components2) const;

    std::vector<std::pair<std::string, std::string>> m_groups;
    AABBCollisionCallback m_callback {nullptr};
};

} // namespace Jackbengine

#endif // __AABB_COLLISION_SYSTEM_H__
