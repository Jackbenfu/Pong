//
//  pongMenu.h
//  Pong
//
//  Created by Damien Bendejacq on 27/07/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __PONG_MENU_H__
#define __PONG_MENU_H__

#include "jackbengine.h"

class PongMenu : public TypedScene<PongMenu>
{
public:
    PongMenu();
    ~PongMenu();

private:
    void frame(float delta) override;
    const char* name() override;
    bool initContents() override;

    TmxSceneLoader *m_tmxLoader {nullptr};

    // Mouse callbacks
    static void onPlayClick(void *data);
    static void onQuitClick(void *data);
    static void onButtonEnter(void *data);
    static void onButtonExit(void *data);
};

#endif // __PONG_MENU_H__
