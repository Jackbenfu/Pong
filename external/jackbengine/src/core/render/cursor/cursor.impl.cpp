//
// cursor.impl.cpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "cursor.impl.hpp"

using namespace Jackbengine;

Cursor::Impl::~Impl()
{
    SDL_FreeCursor(m_cursor);
}

void Cursor::Impl::setCursor(CursorType cursor)
{
    SDL_SystemCursor id;

    switch (cursor)
    {
        case CursorType::Hand:
            id = SDL_SYSTEM_CURSOR_HAND;
            break;

        case CursorType::Default:
            id = SDL_SYSTEM_CURSOR_ARROW;
            break;

        default:
            throw std::runtime_error("Invalid cursor");
    }

    if (nullptr != m_cursor)
    {
        SDL_FreeCursor(m_cursor);
    }

    m_cursor = SDL_CreateSystemCursor(id);
    SDL_SetCursor(m_cursor);
}

void Cursor::Impl::showCursor(bool visible)
{
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
}
