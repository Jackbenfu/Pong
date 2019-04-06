//
// cursor.hpp
// jackbengine
//
// Created by Damien Bendejacq on 11/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <memory>
#include "common.hpp"

namespace Jackbengine {

enum class CursorType
{
    Default,
    Hand,
};

class Cursor
{
    DISALLOW_COPY_AND_MOVE(Cursor)

public:
    Cursor();
    ~Cursor();

    void setCursor(CursorType cursor);

    void showCursor(bool visible);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace Jackbengine

#endif // __CURSOR_H__
