//
// debugTextSystem.cpp
// jackbengine
//
// Created by Damien Bendejacq on 20/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "debugTextSystem.hpp"
#include "component/layout/containerComponent.hpp"
#include "component/view/textComponent.hpp"

using namespace Jackbengine;

DebugTextSystem::DebugTextSystem(Renderer& renderer)
    : DebugTextSystem {renderer, Color32(255, 0, 0)}
{ }

DebugTextSystem::DebugTextSystem(Renderer& renderer, Color32 color)
    : m_renderer {renderer},
      m_color {color}
{ }

int DebugTextSystem::order() const
{
    return (int)SystemOrder::DebugText;
}

void DebugTextSystem::frame(float)
{
    for (const auto& entity : m_entities)
    {
        const auto components = entity.second;

        const auto& container = components->get<ContainerComponent>();

        const Vec2i position {container.x(), container.y()};
        const float w = container.width();
        const float h = container.height();

        const auto x1 = position.x;
        const auto x2 = position.x + w;
        const auto y1 = position.y;
        const auto y2 = position.y + h;

        m_renderer.renderLine(x1, y1, x2, y1, m_color);
        m_renderer.renderLine(x2, y1, x2, y2, m_color);
        m_renderer.renderLine(x2, y2, x1, y2, m_color);
        m_renderer.renderLine(x1, y2, x1, y1, m_color);
    }
}

bool DebugTextSystem::hasRequiredComponents(ComponentCollection& components) const
{
    return components.any<TextComponent>()
        && components.any<ContainerComponent>();
}
