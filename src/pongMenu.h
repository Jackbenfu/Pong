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

    TmxMap *m_tmxLevel = nullptr;

    // Entities
    Entity *m_background = nullptr;
    Entity *m_title = nullptr;
    Entity *m_play = nullptr;
    Entity *m_quit = nullptr;
    Entity *m_author = nullptr;

    // Systems
    SpriteRenderSystem *m_spriteRenderSystem = nullptr;
    TextRenderSystem *m_textRenderSystem = nullptr;
    MouseEventTriggerSystem *m_mouseEventTriggerSystem = nullptr;
    DebugProfileSystem *m_debugProfileSystem = nullptr;

    // Mouse callbacks
    static void onPlayClick(void *data);
    static void onQuitClick(void *data);
    static void onButtonEnter(void *data);
    static void onButtonExit(void *data);
};

#endif // __PONG_MENU_H__
