//
// mouseEventTriggerSystem.cpp
// jackbengine
//
// Created by Damien Bendejacq on 09/09/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "mouseEventTriggerSystem.hpp"
#include "component/layout/containerComponent.hpp"
#include "component/input/mouseListenerComponent.hpp"
#include "component/layout/zOrderComponent.hpp"

using namespace Jackbengine;

MouseEventTriggerSystem::MouseEventTriggerSystem(const Input& input)
    : m_input {input}
{ }

int MouseEventTriggerSystem::order() const
{
    return (int)SystemOrder::MouseEventTrigger;
}

void MouseEventTriggerSystem::setBubbling(bool active)
{
    m_bubbling = active;
}

void MouseEventTriggerSystem::frame(float)
{
    MouseListenerComponent *clickedMouseListener {nullptr};
    auto maxZOrder = 0;

    for (const auto& entity : m_entities)
    {
        const auto components = entity.second;

        const auto& container = components->get<ContainerComponent>();
        auto& mouseListener = components->get<MouseListenerComponent>();

        auto hadEnter = mouseListener.hasEvent(MouseEvent_Enter);
        auto mousePos = m_input.mousePosition();
        auto move = m_input.mouseMove();

        if (container.contains(mousePos))
        {
            if (m_input.mouseClick(MouseButton::Left))
            {
                if (m_bubbling)
                {
                    mouseListener.callLeftClick();
                    continue;
                }

                if (!components->any<ZOrderComponent>())
                {
                    mouseListener.callLeftClick();
                    continue;
                }

                auto& zOrder = components->get<ZOrderComponent>();
                auto currentZOrderIndex = zOrder.index();
                if (currentZOrderIndex >= maxZOrder)
                {
                    maxZOrder = currentZOrderIndex;
                    clickedMouseListener = &mouseListener;
                }
            }

            if (move)
            {
                if (!hadEnter)
                {
                    mouseListener.callOnEnter();
                    mouseListener.removeEvent(MouseEvent_Exit);
                }

                mouseListener.callOnHover();
            }
        }
        else if (move && hadEnter)
        {
            mouseListener.callOnExit();
            mouseListener.removeEvent(MouseEvent_Enter);
            mouseListener.removeEvent(MouseEvent_Hover);
        }
    }

    if (nullptr != clickedMouseListener)
    {
        clickedMouseListener->callLeftClick();
    }
}

bool MouseEventTriggerSystem::hasRequiredComponents(ComponentCollection& components) const
{
    return components.any<ContainerComponent>()
        && components.any<MouseListenerComponent>();
}
