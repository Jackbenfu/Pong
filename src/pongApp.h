//
//  pongApp.h
//  Pong
//
//  Created by Damien Bendejacq on 17/08/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __PONG_APP_H__
#define __PONG_APP_H__

#include "jackbengine.h"

class PongApp : public Application
{
public:
    PongApp(bool fullscreen);
    ~PongApp();

private:
    bool configure(ApplicationConfig& config) override;

    bool m_fullscreen = false;
};

#endif // __PONG_APP_H__
