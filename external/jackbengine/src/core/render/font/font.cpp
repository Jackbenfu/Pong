//
// font.cpp
// jackbengine
//
// Created by Damien Bendejacq on 13/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "font.hpp"
#include "font.impl.hpp"

using namespace Jackbengine;

Font::Font(const std::string& file, int size)
    : m_impl {std::make_unique<Impl>(file, size)}
{ }

Font::Font(const void *data, size_t dataSize, int size)
    : m_impl {std::make_unique<Impl>(data, dataSize, size)}
{ }

Font::~Font() = default;

void Font::glyphMetrics(ushort glyph, int *minX, int *maxX, int *minY, int *maxY, int *advance) const
{
    m_impl->glyphMetrics(glyph, minX, maxX, minY, maxY, advance);
}

void Font::glyphMinX(ushort glyph, int *minX) const
{
    m_impl->glyphMinX(glyph, minX);
}

void Font::glyphMaxX(ushort glyph, int *maxX) const
{
    m_impl->glyphMaxX(glyph, maxX);
}

void Font::glyphMinY(ushort glyph, int *minY) const
{
    m_impl->glyphMinY(glyph, minY);
}

void Font::glyphMaxY(ushort glyph, int *maxY) const
{
    m_impl->glyphMaxY(glyph, maxY);
}

void Font::glyphAdvance(ushort glyph, int *advance) const
{
    m_impl->glyphMinX(glyph, advance);
}

int Font::ascent() const
{
    return m_impl->ascent();
}

int Font::descent() const
{
    return m_impl->descent();
}

int Font::lineSkip() const
{
    return m_impl->lineSkip();
}

void* Font::internalObject() const
{
    return m_impl->internalObject();
}
