//
// renderer.cpp
// jackbengine
//
// Created by Damien Bendejacq on 12/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include "renderer.hpp"
#include "renderer.impl.hpp"

using namespace Jackbengine;

Renderer::Renderer(const Window& window)
    : m_impl {std::make_unique<Impl>(window)}
{ }

Renderer::~Renderer() = default;

void Renderer::clear()
{
    m_impl->clear();
}

void Renderer::present()
{
    m_impl->present();
}

void Renderer::setClearColor(Color32 color)
{
    m_impl->setClearColor(color);
}

void Renderer::setRenderColor(Color32 color)
{
    m_impl->setRenderColor(color);
}

void Renderer::renderTexture(int x, int y, const Texture& texture)
{
    m_impl->renderTexture(x, y, texture);
}

void Renderer::renderTexture(int x, int y, const Texture& texture, double angle)
{
    m_impl->renderTexture(x, y, texture, angle);
}

void Renderer::renderLine(float x1, float y1, float x2, float y2, Color32 color)
{
    m_impl->renderLine(x1, y1, x2, y2, color);
}

void Renderer::renderPoint(float x, float y, Color32 color)
{
    m_impl->renderPoint(x, y, color);
}

int Renderer::width() const
{
    return m_impl->width();
}

int Renderer::height() const
{
    return m_impl->height();
}

void* Renderer::internalObject() const
{
    return m_impl->internalObject();
}
