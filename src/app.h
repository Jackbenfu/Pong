//
//  app.h
//  Pong
//
//  Created by Damien Bendejacq on 17/08/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __APP_H__
#define __APP_H__

#include "jackbengine.h"

class App : public Application
{
public:
    App(bool fullscreen);
    ~App();

private:
    bool configure(ApplicationConfig& config) override;

    bool m_fullscreen = false;
};

#endif // __APP_H__
