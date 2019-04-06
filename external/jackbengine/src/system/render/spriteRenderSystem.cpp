//
// spriteRenderSystem.cpp
// jackbengine
//
// Created by Damien Bendejacq on 21/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "spriteRenderSystem.hpp"
#include "component/view/spriteComponent.hpp"
#include "component/body/transformComponent.hpp"

using namespace Jackbengine;

SpriteRenderSystem::SpriteRenderSystem(Renderer& renderer)
    : m_renderer {renderer}
{ }

int SpriteRenderSystem::order() const
{
    return (int)SystemOrder::SpriteRender;
}

void SpriteRenderSystem::frame(float)
{
    for (const auto entity : m_entities)
    {
        const auto components = entity.second;

        const auto& sprite = components->get<SpriteComponent>();
        const auto& transform = components->get<TransformComponent>();

        m_renderer.renderTexture(
            (int) transform.positionX(),
            (int) transform.positionY(), sprite.texture(), transform.angle()
        );
    }
}

bool SpriteRenderSystem::hasRequiredComponents(ComponentCollection& components) const
{
    return components.any<SpriteComponent>()
        && components.any<TransformComponent>();
}
