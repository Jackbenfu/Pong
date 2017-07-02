//
//  app.h
//  Pong
//
//  Created by Damien Bendejacq on 17/08/2015.
//  Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __APP_H__
#define __APP_H__

#include "jackbengine.hpp"

class App : public Jackbengine::Application
{
public:
    explicit App(bool fullscreen);
    ~App() override;

private:
    bool configure(Jackbengine::ApplicationConfig& config) override;

    bool m_fullscreen = false;
};

#endif // __APP_H__
