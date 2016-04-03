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
    PongApp();
    ~PongApp();

private:
    bool configure(ApplicationConfig& config) override;
};

#endif // __PONG_APP_H__
