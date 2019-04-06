//
// textComponent.hpp
// jackbengine
//
// Created by Damien Bendejacq on 05/08/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __TEXT_COMPONENT_H__
#define __TEXT_COMPONENT_H__

#include "component/component.hpp"
#include "core/render/color32.hpp"
#include "core/render/font/font.hpp"
#include "core/math/rect.hpp"
#include "core/render/renderer/renderer.hpp"
#include "core/render/texture/texture.hpp"

namespace Jackbengine {

enum class TextLayout
{
    LeftTop,
    LeftCenter,
    LeftBottom,
    CenterTop,
    CenterCenter,
    CenterBottom,
    RightTop,
    RightCenter,
    RightBottom,
};

class TextComponent : public Component
{
    DISALLOW_COPY_AND_MOVE(TextComponent)

public:
    TextComponent(const Renderer& renderer, const std::string& text, TextLayout layout, Color32 foreground,
                   int size, const void *fontData, size_t fontDataSize);

    ~TextComponent() override = default;

    const std::string& text() const;
    void setText(const std::string& text);

    Color32 foreground() const;
    void setForeground(Color32 color);
    void setForeground(byte r, byte g, byte b);
    void setForeground(byte r, byte g, byte b, byte a);

    float width() const;
    float height() const;

    int topWhiteSpace() const;
    int bottomWhiteSpace() const;
    int rightWhiteSpace() const;

    TextLayout layout() const;
    void setLayout(TextLayout layout);

    Texture& texture() const;

private:
    void refreshTexture();

    const Renderer& m_renderer;

    std::unique_ptr<Font> m_font;

    std::string m_text;
    TextLayout m_layout;
    Color32 m_foreground;
    int m_size;
    const void *m_fontData;
    const size_t m_fontDataSize;

    std::unique_ptr<Texture> m_texture;

    int m_topWhiteSpace {0};
    int m_bottomWhiteSpace {0};
    int m_rightWhiteSpace {0};
};

using Text = TextComponent;

} // namespace Jackbengine

#endif // __TEXT_COMPONENT_H__
