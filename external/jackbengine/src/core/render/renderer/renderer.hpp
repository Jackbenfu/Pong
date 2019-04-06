//
// renderer.hpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <memory>
#include "core/render/color32.hpp"
#include "core/render/window/window.hpp"

namespace Jackbengine {

class Texture;

class Renderer
{
    friend class Texture;

    DISALLOW_COPY_AND_MOVE(Renderer)

public:
    explicit Renderer(const Window& window);
    ~Renderer();

    void clear();
    void present();

    void setClearColor(Color32 color);
    void setRenderColor(Color32 color);

    void renderTexture(int x, int y, const Texture& texture);
    void renderTexture(int x, int y, const Texture& texture, double angle);
    void renderLine(float x1, float y1, float x2, float y2, Color32 color);
    void renderPoint(float x, float y, Color32 color);

    int width() const;
    int height() const;

private:
    void* internalObject() const;

    class Impl;
    std::unique_ptr<Impl> m_impl;
};

} // namespace Jackbengine

#endif // __RENDERER_H__
