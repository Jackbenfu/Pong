//
//  menuScene.h
//  Pong
//
//  Created by Damien Bendejacq on 27/07/2015.
//  Copyright © 2015 Damien Bendejacq. All rights reserved.
//

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "jackbengine.hpp"
#include "menuSceneLoader.h"

class MenuScene : public Jackbengine::Scene
{
public:
    MenuScene();
    ~MenuScene() override;

    const char* name() override;

private:
    void frame(float delta) override;
    bool initContents() override;

    MenuSceneLoader *m_sceneLoader = nullptr;

    // Mouse callbacks
    static void onPlayClick(Jackbengine::Scene *scene, void *data);
    static void onQuitClick(Jackbengine::Scene *scene, void *data);
    static void onButtonEnter(Jackbengine::Scene *scene, void *data);
    static void onButtonExit(Jackbengine::Scene *scene, void *data);
};

#endif // __MENU_SCENE_H__
