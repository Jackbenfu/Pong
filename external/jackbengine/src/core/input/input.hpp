//
// input.hpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __INPUT_H__
#define __INPUT_H__

#include <memory>
#include "keyboardKey.hpp"
#include "mouseButton.hpp"
#include "core/math/vector2d.hpp"

namespace Jackbengine {

class Input
{
    DISALLOW_COPY_AND_MOVE(Input)

public:
    Input();
    ~Input();

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
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace Jackbengine

#endif // __INPUT_H__
