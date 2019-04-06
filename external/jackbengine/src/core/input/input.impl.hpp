//
// input.impl.hpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __INPUT_IMPL_H__
#define __INPUT_IMPL_H__

#include <vector>
#include "input.hpp"
#include "platform.hpp"

namespace Jackbengine {

class Input::Impl
{
public:
    Impl() = default;

    void update();

    bool keyDown(KeyboardKey key) const;
    bool keyUp(KeyboardKey key) const;
    bool keyPress(KeyboardKey key) const;

    bool mouseDown(MouseButton button) const;
    bool mouseUp(MouseButton button) const;
    bool mouseClick(MouseButton button) const;
    bool mouseMove() const;
    const Vec2i& mousePosition() const;

    bool quit() const;

private:
    int getKey(KeyboardKey key) const;
    int getButton(MouseButton button) const;

    std::vector<bool> m_keyboardKeysDown = std::vector<bool>(SDL_NUM_SCANCODES, false);
    std::vector<bool> m_keyboardKeysPress = std::vector<bool>(SDL_NUM_SCANCODES, false);

    // Hard coded max mouse button number, SDL does not provide the info
    // We only support the three basic mouse buttons: left, middle and right
    // Need to set it to 4 instead of 3, because the first button starts at 1, not 0
    const uint MaxMouseButtons {4};

    std::vector<bool> m_mouseButtonsDown = std::vector<bool>(MaxMouseButtons, false);
    std::vector<bool> m_mouseButtonsClick = std::vector<bool>(MaxMouseButtons, false);

    mutable Vec2i m_mousePos;

    bool m_mouseMove {false};

    bool m_quit {false};
};

} // namespace Jackbengine

#endif // __INPUT_IMPL_H__
