//
// font.impl.hpp
// jackbengine
//
// Created by Damien Bendejacq on 13/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __FONT_IMPL_H__
#define __FONT_IMPL_H__

#include "font.hpp"
#include "platform.hpp"

namespace Jackbengine {

class Font::Impl
{
public:
    Impl(const std::string& file, int size);
    Impl(const void *data, size_t dataSize, int size);

    ~Impl();

    void glyphMetrics(ushort glyph, int *minX, int *maxX, int *minY, int *maxY, int *advance) const;

    void glyphMinX(ushort glyph, int *minX) const;
    void glyphMaxX(ushort glyph, int *maxX) const;
    void glyphMinY(ushort glyph, int *minY) const;
    void glyphMaxY(ushort glyph, int *maxY) const;
    void glyphAdvance(ushort glyph, int *advance) const;

    int ascent() const;
    int descent() const;
    int lineSkip() const;

    TTF_Font* internalObject() const;

private:
    TTF_Font *m_font {nullptr};
};

} // namespace Jackbengine

#endif // __FONT_IMPL_H__
