//
// menuSceneLoader.h
// Pong
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright © 2016 Damien Bendejacq. All rights reserved.
//

#ifndef __MENU_SCENE_LOADER_H__
#define __MENU_SCENE_LOADER_H__

#include "jackbengine.hpp"

class MenuSceneLoader : public Jackbengine::TmxSceneLoader
{
public:
    explicit MenuSceneLoader(Jackbengine::Scene *scene);
    ~MenuSceneLoader() override;

private:
    bool loadContents() override;

    const char *TILESET_FILE = "tileset.png";
};

#endif // __MENU_SCENE_LOADER_H__
