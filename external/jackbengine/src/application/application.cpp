//
// application.cpp
// jackbengine
//
// Created by Damien Bendejacq on 10/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#include <ctime>
#include "application.hpp"

using namespace Jackbengine;

Application::Application(ApplicationConfig& config)
    : m_timer(config.core_fps),
      m_window(
        config.general_title,
        config.render_width,
        config.render_height,
        config.render_fullscreen
      ),
      m_renderer(m_window)
{
    srand(static_cast<uint>(time(nullptr)));
}

bool Application::running() const
{
    return m_running;
}

void Application::loop()
{
    m_timer.start();

    const auto deltaMultiplier = 0.001f;
    const auto delta = m_timer.elapsedMilliseconds() * deltaMultiplier;

    m_renderer.clear();
    m_input.update();

    frame(delta);

    m_renderer.present();

    if (m_input.quit())
    {
        exit();
    }

    m_timer.snapshot();
}

Timer& Application::timer() const
{
    return m_timer;
}

Cursor& Application::cursor() const
{
    return m_cursor;
}

Input& Application::input() const
{
    return m_input;
}

Window& Application::window() const
{
    return m_window;
}

Renderer& Application::renderer() const
{
    return m_renderer;
}

void Application::exit()
{
    m_running = false;
}
