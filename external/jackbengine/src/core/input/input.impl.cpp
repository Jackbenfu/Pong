//
// input.impl.cpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "input.impl.hpp"

using namespace Jackbengine;

void Input::Impl::update()
{
    std::fill(m_keyboardKeysPress.begin(), m_keyboardKeysPress.end(), false);
    std::fill(m_mouseButtonsClick.begin(), m_mouseButtonsClick.end(), false);
    m_mouseMove = false;

    SDL_Event event {};
    while (SDL_PollEvent(&event) > 0)
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
            {
                m_keyboardKeysDown[event.key.keysym.scancode] = true;
                break;
            }

            case SDL_KEYUP:
            {
                const auto scancode = event.key.keysym.scancode;
                if (m_keyboardKeysDown[scancode])
                {
                    m_keyboardKeysPress[scancode] = true;
                }
                m_keyboardKeysDown[scancode] = false;

                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                const auto mouseState = SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);

                if ((bool)(mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)))
                {
                    m_mouseButtonsDown[SDL_BUTTON_LEFT] = true;
                }
                else
                {
                    if (m_mouseButtonsDown[SDL_BUTTON_LEFT])
                    {
                        m_mouseButtonsClick[SDL_BUTTON_LEFT] = true;
                    }

                    m_mouseButtonsDown[SDL_BUTTON_LEFT] = false;
                }

                if ((bool)(mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE)))
                {
                    if (m_mouseButtonsDown[SDL_BUTTON_MIDDLE])
                    {
                        m_mouseButtonsClick[SDL_BUTTON_MIDDLE] = true;
                    }

                    m_mouseButtonsDown[SDL_BUTTON_MIDDLE] = true;
                }
                else
                {
                    m_mouseButtonsDown[SDL_BUTTON_MIDDLE] = false;
                }

                if ((bool)(mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT)))
                {
                    if (m_mouseButtonsDown[SDL_BUTTON_RIGHT])
                    {
                        m_mouseButtonsClick[SDL_BUTTON_RIGHT] = true;
                    }

                    m_mouseButtonsDown[SDL_BUTTON_RIGHT] = true;
                }
                else
                {
                    m_mouseButtonsDown[SDL_BUTTON_RIGHT] = false;
                }

                break;
            }

            case SDL_MOUSEMOTION:
            {
                m_mouseMove = true;
                break;
            }

            case SDL_QUIT:
            {
                m_quit = true;
                break;
            }

            default:
                break;
        }
    }
}

bool Input::Impl::keyDown(KeyboardKey key) const
{
    return m_keyboardKeysDown[getKey(key)];
}

bool Input::Impl::keyUp(KeyboardKey key) const
{
    return !m_keyboardKeysDown[getKey(key)];
}

bool Input::Impl::keyPress(KeyboardKey key) const
{
    return m_keyboardKeysPress[getKey(key)];
}

bool Input::Impl::mouseDown(MouseButton button) const
{
    return m_mouseButtonsDown[getButton(button)];
}

bool Input::Impl::mouseUp(MouseButton button) const
{
    return !m_mouseButtonsDown[getButton(button)];
}

bool Input::Impl::mouseClick(MouseButton button) const
{
    return m_mouseButtonsClick[getButton(button)];
}

bool Input::Impl::mouseMove() const
{
    return m_mouseMove;
}

const Vec2i& Input::Impl::mousePosition() const
{
    SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);

    return m_mousePos;
}

bool Input::Impl::quit() const
{
    return m_quit;
}

int Input::Impl::getKey(KeyboardKey key) const
{
    switch (key)
    {
        case KeyboardKey::A:            return SDL_SCANCODE_A;
        case KeyboardKey::B:            return SDL_SCANCODE_B;
        case KeyboardKey::C:            return SDL_SCANCODE_C;
        case KeyboardKey::D:            return SDL_SCANCODE_D;
        case KeyboardKey::E:            return SDL_SCANCODE_E;
        case KeyboardKey::F:            return SDL_SCANCODE_F;
        case KeyboardKey::G:            return SDL_SCANCODE_G;
        case KeyboardKey::H:            return SDL_SCANCODE_H;
        case KeyboardKey::I:            return SDL_SCANCODE_I;
        case KeyboardKey::J:            return SDL_SCANCODE_J;
        case KeyboardKey::K:            return SDL_SCANCODE_K;
        case KeyboardKey::L:            return SDL_SCANCODE_L;
        case KeyboardKey::M:            return SDL_SCANCODE_M;
        case KeyboardKey::N:            return SDL_SCANCODE_N;
        case KeyboardKey::O:            return SDL_SCANCODE_O;
        case KeyboardKey::P:            return SDL_SCANCODE_P;
        case KeyboardKey::Q:            return SDL_SCANCODE_Q;
        case KeyboardKey::R:            return SDL_SCANCODE_R;
        case KeyboardKey::S:            return SDL_SCANCODE_S;
        case KeyboardKey::T:            return SDL_SCANCODE_T;
        case KeyboardKey::U:            return SDL_SCANCODE_U;
        case KeyboardKey::V:            return SDL_SCANCODE_V;
        case KeyboardKey::W:            return SDL_SCANCODE_W;
        case KeyboardKey::X:            return SDL_SCANCODE_X;
        case KeyboardKey::Y:            return SDL_SCANCODE_Y;
        case KeyboardKey::Z:            return SDL_SCANCODE_Z;

        case KeyboardKey::DIGIT_1:      return SDL_SCANCODE_1;
        case KeyboardKey::DIGIT_2:      return SDL_SCANCODE_2;
        case KeyboardKey::DIGIT_3:      return SDL_SCANCODE_3;
        case KeyboardKey::DIGIT_4:      return SDL_SCANCODE_4;
        case KeyboardKey::DIGIT_5:      return SDL_SCANCODE_5;
        case KeyboardKey::DIGIT_6:      return SDL_SCANCODE_6;
        case KeyboardKey::DIGIT_7:      return SDL_SCANCODE_7;
        case KeyboardKey::DIGIT_8:      return SDL_SCANCODE_8;
        case KeyboardKey::DIGIT_9:      return SDL_SCANCODE_9;
        case KeyboardKey::DIGIT_0:      return SDL_SCANCODE_0;

        case KeyboardKey::Return:       return SDL_SCANCODE_RETURN;
        case KeyboardKey::Escape:       return SDL_SCANCODE_ESCAPE;
        case KeyboardKey::Backspace:    return SDL_SCANCODE_BACKSPACE;
        case KeyboardKey::Tab:          return SDL_SCANCODE_TAB;
        case KeyboardKey::Space:        return SDL_SCANCODE_SPACE;

        case KeyboardKey::F1:           return SDL_SCANCODE_F1;
        case KeyboardKey::F2:           return SDL_SCANCODE_F2;
        case KeyboardKey::F3:           return SDL_SCANCODE_F3;
        case KeyboardKey::F4:           return SDL_SCANCODE_F4;
        case KeyboardKey::F5:           return SDL_SCANCODE_F5;
        case KeyboardKey::F6:           return SDL_SCANCODE_F6;
        case KeyboardKey::F7:           return SDL_SCANCODE_F7;
        case KeyboardKey::F8:           return SDL_SCANCODE_F8;
        case KeyboardKey::F9:           return SDL_SCANCODE_F9;
        case KeyboardKey::F10:          return SDL_SCANCODE_F10;
        case KeyboardKey::F11:          return SDL_SCANCODE_F11;
        case KeyboardKey::F12:          return SDL_SCANCODE_F12;

        case KeyboardKey::Down:         return SDL_SCANCODE_DOWN;
        case KeyboardKey::Right:        return SDL_SCANCODE_RIGHT;
        case KeyboardKey::Left:         return SDL_SCANCODE_LEFT;
        case KeyboardKey::Up:           return SDL_SCANCODE_UP;

        default: throw std::runtime_error("Invalid keyboard key");
    }
}

int Input::Impl::getButton(MouseButton button) const
{
    switch (button)
    {
        case MouseButton::Left:
            return SDL_BUTTON_LEFT;

        case MouseButton::Middle:
            return SDL_BUTTON_MIDDLE;

        case MouseButton::Right:
            return SDL_BUTTON_RIGHT;

        default:
            throw std::runtime_error("Invalid mouse button");
    }
}
