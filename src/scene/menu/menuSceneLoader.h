//
// menuSceneLoader.h
// Jackbengine
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright (c) 2016 Damien Bendejacq. All rights reserved.
//

#ifndef __MENU_SCENE_LOADER_H__
#define __MENU_SCENE_LOADER_H__

#include "jackbengine.h"

NS_BEGIN_JKB

class MenuSceneLoader : public TmxSceneLoader
{
public:
    MenuSceneLoader(Scene *scene);
    ~MenuSceneLoader();

private:
    bool loadContents() override;

    const char *TILESET_FILE = "tileset.png";
};

NS_END_JKB

#endif // __MENU_SCENE_LOADER_H__
