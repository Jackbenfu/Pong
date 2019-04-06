//
// textRenderSystem.cpp
// jackbengine
//
// Created by Damien Bendejacq on 21/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "textRenderSystem.hpp"
#include "component/layout/containerComponent.hpp"
#include "component/view/textComponent.hpp"

using namespace Jackbengine;

TextRenderSystem::TextRenderSystem(Renderer& renderer)
    : m_renderer {renderer}
{ }

int TextRenderSystem::order() const
{
    return (int)SystemOrder::TextRender;
}

void TextRenderSystem::frame(float)
{
    for (const auto entity : m_entities)
    {
        const auto components = entity.second;

        const auto& text = components->get<TextComponent>();
        const auto& container = components->get<ContainerComponent>();

        Vec2f position;
        const auto angle = 0.0;

        switch (text.layout())
        {
            case TextLayout::LeftTop:
            {
                position.x = container.x();
                position.y = container.y();
                break;
            }

            case TextLayout::LeftCenter:
            {
                position.x = container.x();
                position.y = container.y() + container.height() / 2 - text.height() / 2 +
                    text.topWhiteSpace() / 2;
                break;
            }

            case TextLayout::LeftBottom:
            {
                position.x = container.x();
                position.y = container.y() + container.height() - text.height();
                break;
            }

            case TextLayout::CenterTop:
            {
                position.x = container.x() + container.width() / 2 - text.width() / 2 +
                    text.rightWhiteSpace() / 2;
                position.y = container.y();
                break;
            }

            case TextLayout::CenterCenter:
            {
                position.x = container.x() + container.width() / 2 - text.width() / 2 +
                    text.rightWhiteSpace() / 2;
                position.y = container.y() + container.height() / 2 - text.height() / 2 +
                    text.topWhiteSpace() / 2;
                break;
            }

            case TextLayout::CenterBottom:
            {
                position.x = container.x() + container.width() / 2 - text.width() / 2 +
                    text.rightWhiteSpace() / 2;
                position.y = container.y() + container.height() - text.height();
                break;
            }

            case TextLayout::RightTop:
            {
                position.x = container.x() + container.width() - text.width();
                position.y = container.y();
                break;
            }

            case TextLayout::RightCenter:
            {
                position.x = container.x() + container.width() - text.width();
                position.y = container.y() + container.height() / 2 - text.height() / 2 +
                    text.topWhiteSpace() / 2;
                break;
            }

            case TextLayout::RightBottom:
            {
                position.x = container.x() + container.width() - text.width();
                position.y = container.y() + container.height() - text.height();
                break;
            }
        }

        m_renderer.renderTexture(
            (int)position.x,
            (int)position.y,
            text.texture(),
            angle
        );
    }
}

bool TextRenderSystem::hasRequiredComponents(ComponentCollection& components) const
{
   return components.any<TextComponent>()
       && components.any<ContainerComponent>();
}
