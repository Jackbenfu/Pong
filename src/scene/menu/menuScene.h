//
//  menuScene.h
//  Pong
//
//  Created by Damien Bendejacq on 27/07/2015.
//  Copyright (c) 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "jackbengine.h"
#include "menuSceneLoader.h"

class MenuScene : public TypedScene<MenuScene>
{
public:
    MenuScene();
    ~MenuScene();

private:
    void frame(float delta) override;
    const char* name() override;
    bool initContents() override;

    MenuSceneLoader *m_sceneLoader {nullptr};

    // Mouse callbacks
    static void onPlayClick(Scene *scene, void *data);
    static void onQuitClick(Scene *scene, void *data);
    static void onButtonEnter(Scene *scene, void *data);
    static void onButtonExit(Scene *scene, void *data);
};

#endif // __MENU_SCENE_H__
