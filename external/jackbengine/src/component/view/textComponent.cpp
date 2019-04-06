//
// textComponent.cpp
// jackbengine
//
// Created by Damien Bendejacq on 05/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "textComponent.hpp"

using namespace Jackbengine;

TextComponent::TextComponent(const Renderer& renderer, const std::string& text, TextLayout layout, Color32 foreground,
                               int size, const void *fontData, size_t fontDataSize)
    : m_renderer {renderer},
      m_text {text},
      m_layout {layout},
      m_foreground {foreground},
      m_size {size},
      m_fontData {fontData},
      m_fontDataSize {fontDataSize}
{
    refreshTexture();
}

const std::string& TextComponent::text() const
{
    return m_text;
}

void TextComponent::setText(const std::string& text)
{
    m_text = text;

    refreshTexture();
}

Color32 TextComponent::foreground() const
{
    return m_foreground;
}

void TextComponent::setForeground(Color32 color)
{
    m_foreground = color;

    refreshTexture();
}

void TextComponent::setForeground(byte r, byte g, byte b)
{
    m_foreground = Color32(r, g, b);

    refreshTexture();
}

void TextComponent::setForeground(byte r, byte g, byte b, byte a)
{
    m_foreground = Color32(r, g, b, a);

    refreshTexture();
}

float TextComponent::width() const
{
    return m_texture->width();
}

float TextComponent::height() const
{
    return m_texture->height();
}

int TextComponent::topWhiteSpace() const
{
    return m_topWhiteSpace;
}

int TextComponent::bottomWhiteSpace() const
{
    return m_bottomWhiteSpace;
}

int TextComponent::rightWhiteSpace() const
{
    return m_rightWhiteSpace;
}

TextLayout TextComponent::layout() const
{
    return m_layout;
}

void TextComponent::setLayout(TextLayout layout)
{
    m_layout = layout;
}

Texture& TextComponent::texture() const
{
    return *m_texture;
}

void TextComponent::refreshTexture()
{
    m_font = std::make_unique<Font>(m_fontData, m_fontDataSize, m_size);
    m_texture = std::make_unique<Texture>(m_renderer, *m_font, m_text, m_foreground);

    auto glyphMaxY = 0;
    auto lastGlyphAdvance = 0;
    auto lastGlyphMaxX = 0;
    for (size_t i = 0; i < m_text.length(); ++i)
    {
        int glyphY;
        if (m_text.length() - 1 > i)
        {
            m_font->glyphMaxY((ushort) m_text[i], &glyphY);
        }
        else
        {
            int minX;
            int minY;
            m_font->glyphMetrics((ushort) m_text[i], &minX, &lastGlyphMaxX, &minY, &glyphY, &lastGlyphAdvance);
        }

        if (glyphY > glyphMaxY)
        {
            glyphMaxY = glyphY;
        }
    }

    m_bottomWhiteSpace = abs(m_font->descent());
    m_topWhiteSpace = m_font->lineSkip() - glyphMaxY - m_bottomWhiteSpace;
    m_rightWhiteSpace = lastGlyphAdvance - lastGlyphMaxX;
}
