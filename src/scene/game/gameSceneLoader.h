//
// gameSceneLoader.h
// Jackbengine
//
// Created by Damien Bendejacq on 17/09/2016.
// Copyright (c) 2016 Damien Bendejacq. All rights reserved.
//

#ifndef __GAME_SCENE_LOADER_H__
#define __GAME_SCENE_LOADER_H__

#include "jackbengine.h"

NS_BEGIN_JKB

class GameSceneLoader : public TmxSceneLoader
{
public:
    GameSceneLoader(Scene *scene);
    ~GameSceneLoader();

    int getMaxScore() const;

private:
    bool loadContents() override;

    void loadSystems();

    // Level loading
    void loadBackground();
    void loadWall(const char *name);
    void loadPaddle(const char *name, const void *soundData, size_t soundDataSize);
    void loadBall();
    void loadScore(const char *name);
    void loadGameOver();
    void loadResult(const char *name);
    Entity* loadInstruction(
        const char *group, const char *name, const char *text,
        TextLayout textLayout, Color color);

    char *m_goal2Text {nullptr};
};

NS_END_JKB

#endif // __GAME_SCENE_LOADER_H__
