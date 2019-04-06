//
// application.hpp
// jackbengine
//
// Created by Damien Bendejacq on 10/07/2017.
// Copyright © 2017 Damien Bendejacq. All rights reserved.
//

#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "applicationConfig.hpp"
#include "abstract/abstractApplication.hpp"

#include "core/input/input.hpp"
#include "core/render/cursor/cursor.hpp"
#include "core/render/renderer/renderer.hpp"
#include "core/render/window/window.hpp"
#include "core/time/timer.hpp"

namespace Jackbengine {

class Application : public AbstractApplication
{
    DISALLOW_COPY_AND_MOVE(Application)

public:
    Application() = delete;
    explicit Application(ApplicationConfig& config);
    virtual ~Application() = default;

    bool running() const;
    void loop();

    virtual void frame(float delta) = 0;

    Timer& timer() const;
    Cursor& cursor() const;
    Input& input() const;
    Window& window() const;
    Renderer& renderer() const;

    void exit();

private:
    mutable Timer m_timer;
    mutable Cursor m_cursor;
    mutable Input m_input;
    mutable Window m_window;
    mutable Renderer m_renderer;

    bool m_running {true};
};

} // namespace Jackbengine

#endif // __APPLICATION_H__
