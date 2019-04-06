//
// debugSpriteSystem.cpp
// jackbengine
//
// Created by Damien Bendejacq on 19/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "debugSpriteSystem.hpp"
#include "component/body/shape/boxShapeComponent.hpp"
#include "component/body/transformComponent.hpp"
#include "debugProfileSystem.hpp"

using namespace Jackbengine;

DebugSpriteSystem::DebugSpriteSystem(Renderer& renderer)
    : m_renderer {renderer},
      m_color {Color32(255, 0, 0)}
{ }

int DebugSpriteSystem::order() const
{
    return (int)SystemOrder::DebugSprite;
}

void DebugSpriteSystem::frame(float)
{
    for (const auto& entity : m_entities)
    {
        const auto components = entity.second;

        const auto& boxShape = components->get<BoxShapeComponent>();
        const auto& transform = components->get<TransformComponent>();

        const auto position = transform.position();
        const auto size = boxShape.size();

        const auto x1 = position.x;
        const auto x2 = position.x + size.x;
        const auto y1 = position.y;
        const auto y2 = position.y + size.y;

        m_renderer.renderLine(x1, y1, x2, y1, m_color);
        m_renderer.renderLine(x2, y1, x2, y2, m_color);
        m_renderer.renderLine(x2, y2, x1, y2, m_color);
        m_renderer.renderLine(x1, y2, x1, y1, m_color);
    }
}

bool DebugSpriteSystem::hasRequiredComponents(ComponentCollection& components) const
{
    return components.any<BoxShapeComponent>()
        && components.any<TransformComponent>();
}
