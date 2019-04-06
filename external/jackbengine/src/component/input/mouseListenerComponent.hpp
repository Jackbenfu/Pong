//
// mouseListenerComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 07/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __MOUSE_LISTENER_COMPONENT_H__
#define __MOUSE_LISTENER_COMPONENT_H__

#include <functional>
#include "component/component.hpp"

namespace Jackbengine {

using MouseCallback = std::function<void()>;

enum MouseEvent
{
    MouseEvent_LeftClick = 1,
    MouseEvent_MiddleClick = 2,
    MouseEvent_RightClick = 4,
    MouseEvent_Hover = 8,
    MouseEvent_Enter = 16,
    MouseEvent_Exit = 32,
};

class MouseListenerComponent : public Component
{
    friend class MouseEventTriggerSystem;

    DISALLOW_COPY_AND_MOVE(MouseListenerComponent)

public:
    MouseListenerComponent() = default;
    ~MouseListenerComponent() override = default;

    void onLeftClick(MouseCallback callback);
    void onLeftDown(MouseCallback callback);

    void onMiddleClick(MouseCallback callback);
    void onMiddleDown(MouseCallback callback);

    void onRightClick(MouseCallback callback);
    void onRightDown(MouseCallback callback);

    void onHover(MouseCallback callback);
    void onEnter(MouseCallback callback);
    void onExit(MouseCallback callback);

    bool leftClick();
    bool middleClick();
    bool rightClick();
    bool hover() const;
    bool enter() const;
    bool exit() const;

private:
    MouseCallback m_onLeftClick {nullptr};
    void callLeftClick();

    MouseCallback m_onLeftDown {nullptr};
    void callLeftDown() const;

    MouseCallback m_onMiddleClick {nullptr};
    void callMiddleClick();

    MouseCallback m_onMiddleDown {nullptr};
    void callMiddleDown() const;

    MouseCallback m_onRightClick {nullptr};
    void callRightClick();

    MouseCallback m_onRightDown {nullptr};
    void callRightDown() const;

    MouseCallback m_onHover {nullptr};
    void callOnHover();

    MouseCallback m_onEnter {nullptr};
    void callOnEnter();

    MouseCallback m_onExit {nullptr};
    void callOnExit();

    uint m_events {0};

    void addEvent(MouseEvent event);
    void removeEvent(MouseEvent event);
    bool hasEvent(MouseEvent event) const;
    bool hasAndRemoveEvent(MouseEvent event);
};

using MouseListener = MouseListenerComponent;

} // namespace Jackbengine

#endif // __MOUSE_LISTENER_COMPONENT_H__
