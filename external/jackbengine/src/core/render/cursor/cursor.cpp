//
// cursor.cpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "cursor.hpp"
#include "cursor.impl.hpp"

using namespace Jackbengine;

Cursor::Cursor()
    : m_impl {std::make_unique<Impl>()}
{ }

Cursor::~Cursor() = default;

void Cursor::setCursor(CursorType cursor)
{
    m_impl->setCursor(cursor);
}

void Cursor::showCursor(bool visible)
{
    m_impl->showCursor(visible);
}
