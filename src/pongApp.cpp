//
//  pongApp.cpp
//  Pong
//
//  Created by Damien Bendejacq on 17/08/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#include "pongApp.h"
#include "pongMenu.h"
#include "pongGame.h"

PongApp::PongApp()
{
}

PongApp::~PongApp()
{
}

bool PongApp::configure(ApplicationConfig& config)
{
    config.general_title = "Pong";
    config.render_width = 768;
    config.render_height = 576;

    srand(static_cast<uint>(time(nullptr)));

    addScene<PongMenu>();
    addScene<PongGame>();

    return true;
}
